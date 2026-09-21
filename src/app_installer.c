/*
 * PS5 Homescreen App Installer for the WebKit Autoloader Installer.
 * Based on the original implementation in ftpsrv by John Törnblom
 * and Payload Manager by X-F1REBALL-X.
 */

#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "app_installer.h"
#include "wkali.h"
#include <ps5/kernel.h>

#define INCASSET(name, file)                                                   \
  __asm__(".section .rodata\n"                                                 \
          ".global " #name "\n"                                                \
          ".global " #name "_end\n"                                            \
          ".global " #name "_size\n"                                           \
          ".align 16\n" #name ":\n"                                            \
          ".incbin \"" file "\"\n" #name "_end:\n" #name "_size:\n"            \
          ".quad " #name "_end - " #name "\n"                                  \
          ".previous\n");                                                      \
  extern const uint8_t name[];                                                 \
  extern const size_t name##_size;

INCASSET(param_json, "assets/param.json");
INCASSET(icon0_png, "assets/icon0.png");
/* pic0 = selected-app homescreen background; also installed as pic1. */
INCASSET(pic0_png, "assets/pic0.png");

int sceAppInstUtilInitialize(void);
int sceAppInstUtilTerminate(void);
int sceAppInstUtilAppInstallAll(void *);
int sceAppInstUtilAppUnInstall(const char *);

/* Path buffers below are built as /user/app/<title_id>/... — title IDs are
 * fixed 9-char strings, so 256 bytes can never truncate. This guard keeps
 * it that way if WKAL_TITLE_ID is ever changed. */
_Static_assert(sizeof(WKAL_TITLE_ID) <= 16, "WKAL_TITLE_ID too long for path buffers");

static int mkdir_p(const char *path, mode_t mode) {
  char tmp[256];
  snprintf(tmp, sizeof(tmp), "%s", path);
  size_t len = strlen(tmp);
  if (len == 0)
    return 0;
  if (tmp[len - 1] == '/')
    tmp[len - 1] = '\0';
  for (char *p = tmp + 1; *p; p++) {
    if (*p == '/') {
      *p = '\0';
      if (mkdir(tmp, mode) != 0 && errno != EEXIST) {
        return -1;
      }
      *p = '/';
    }
  }
  if (mkdir(tmp, mode) != 0 && errno != EEXIST) {
    return -1;
  }
  return 0;
}

static int install_file(const char *path, const uint8_t *data, size_t size) {
  FILE *f;
  if (!(f = fopen(path, "wb"))) {
    return -1;
  }
  if (fwrite(data, size, 1, f) != 1) {
    fclose(f);
    return -1;
  }
  fclose(f);
  return 0;
}

static int install_app(const char *title_id, const char *dir) {
  int (*sceAppInstUtilAppInstallTitleDir)(const char *, const char *, void *) =
      0;
  const char *nid = "Wudg3Xe3heE";
  uint32_t handle;

  if (!kernel_dynlib_handle(-1, "libSceAppInstUtil.sprx", &handle)) {
    sceAppInstUtilAppInstallTitleDir =
        (void *)kernel_dynlib_resolve(-1, handle, nid);
  }

  if (sceAppInstUtilAppInstallTitleDir) {
    return sceAppInstUtilAppInstallTitleDir(title_id, dir, 0);
  }

  return sceAppInstUtilAppInstallAll(0);
}

static int needs_update(const char *path, const uint8_t *expected_data,
                        size_t expected_size) {
  struct stat st;
  if (stat(path, &st) != 0)
    return 1;
  if ((size_t)st.st_size != expected_size)
    return 1;

  FILE *f = fopen(path, "rb");
  if (!f)
    return 1;

  uint8_t *buf = malloc(expected_size);
  if (!buf) {
    fclose(f);
    return 1;
  }

  if (fread(buf, 1, expected_size, f) != expected_size) {
    free(buf);
    fclose(f);
    return 1;
  }
  fclose(f);

  int mismatch = memcmp(buf, expected_data, expected_size);
  free(buf);

  return mismatch != 0;
}

int wkali_app_is_up_to_date(void) {
  const char *title_id = WKAL_TITLE_ID;
  char base_dir[256];
  char param_path[256];
  char icon_path[256];
  char pic0_path[256];
  char pic1_path[256];
  char appmeta_pic0[256];
  struct stat st;

  snprintf(base_dir, sizeof(base_dir), "/user/app/%s", title_id);
  snprintf(param_path, sizeof(param_path), "/user/app/%s/sce_sys/param.json",
           title_id);
  snprintf(icon_path, sizeof(icon_path), "/user/app/%s/sce_sys/icon0.png",
           title_id);
  snprintf(pic0_path, sizeof(pic0_path), "/user/app/%s/sce_sys/pic0.png",
           title_id);
  snprintf(pic1_path, sizeof(pic1_path), "/user/app/%s/sce_sys/pic1.png",
           title_id);
  /* Homescreen focus art is read from appmeta as pic0. */
  snprintf(appmeta_pic0, sizeof(appmeta_pic0), "/user/appmeta/%s/pic0.png",
           title_id);

  if (stat(base_dir, &st) != 0)
    return 0;
  if (needs_update(param_path, param_json, param_json_size))
    return 0;
  if (needs_update(icon_path, icon0_png, icon0_png_size))
    return 0;
  if (needs_update(pic0_path, pic0_png, pic0_png_size))
    return 0;
  if (needs_update(pic1_path, pic0_png, pic0_png_size))
    return 0;
  if (needs_update(appmeta_pic0, pic0_png, pic0_png_size))
    return 0;
  return 1;
}

/* Mirror into /user/appmeta — PS5 home UI reads focus background from here. */
static void mirror_appmeta(const char *title_id) {
  char meta_dir[256];
  char path[256];

  snprintf(meta_dir, sizeof(meta_dir), "/user/appmeta/%s", title_id);
  if (mkdir_p(meta_dir, 0755) != 0) {
    wkali_log("[WKALI] appmeta mkdir failed: %s errno=%d\n", meta_dir, errno);
    return;
  }

  snprintf(path, sizeof(path), "/user/appmeta/%s/param.json", title_id);
  if (install_file(path, param_json, param_json_size))
    wkali_log("[WKALI] appmeta param.json failed\n");

  snprintf(path, sizeof(path), "/user/appmeta/%s/icon0.png", title_id);
  if (install_file(path, icon0_png, icon0_png_size))
    wkali_log("[WKALI] appmeta icon0.png failed\n");

  snprintf(path, sizeof(path), "/user/appmeta/%s/pic0.png", title_id);
  if (install_file(path, pic0_png, pic0_png_size))
    wkali_log("[WKALI] appmeta pic0.png failed\n");

  snprintf(path, sizeof(path), "/user/appmeta/%s/pic1.png", title_id);
  if (install_file(path, pic0_png, pic0_png_size))
    wkali_log("[WKALI] appmeta pic1.png failed\n");
}

int wkali_install_app_if_needed(void) {
  const char *title_id = WKAL_TITLE_ID;
  char base_dir[256];
  char param_path[256];
  char icon_path[256];
  char pic0_path[256];
  char pic1_path[256];
  struct stat st;

  snprintf(base_dir, sizeof(base_dir), "/user/app/%s", title_id);
  snprintf(param_path, sizeof(param_path), "/user/app/%s/sce_sys/param.json",
           title_id);
  snprintf(icon_path, sizeof(icon_path), "/user/app/%s/sce_sys/icon0.png",
           title_id);
  snprintf(pic0_path, sizeof(pic0_path), "/user/app/%s/sce_sys/pic0.png",
           title_id);
  snprintf(pic1_path, sizeof(pic1_path), "/user/app/%s/sce_sys/pic1.png",
           title_id);

  if (wkali_app_is_up_to_date()) {
    return 0; /* Already installed and up to date */
  }

  if (stat(base_dir, &st) == 0) {
    wkali_log("[WKALI] Updating existing app launcher (%s)...\n", title_id);
    wkali_notify("Updating WebKit Autoloader App...");
  } else {
    wkali_log("[WKALI] Installing browser launcher app (%s)...\n", title_id);
    wkali_notify("Installing WebKit Autoloader App...");
  }

  int err;
  if ((err = sceAppInstUtilInitialize())) {
    wkali_log("[WKALI] sceAppInstUtilInitialize: error 0x%08X\n", err);
    return -1;
  }

  /* Drop the old Media/Games registration so category + badge re-apply cleanly. */
  if (stat(base_dir, &st) == 0) {
    err = sceAppInstUtilAppUnInstall(title_id);
    wkali_log("[WKALI] UnInstall %s: 0x%08X\n", title_id, err);
  }

  char sce_sys_dir[256];
  snprintf(sce_sys_dir, sizeof(sce_sys_dir), "/user/app/%s/sce_sys", title_id);
  if (mkdir_p(sce_sys_dir, 0755) != 0) {
    wkali_log("[WKALI] Failed to create app dir: %s (errno: %d)\n",
              sce_sys_dir, errno);
    sceAppInstUtilTerminate();
    return -1;
  }

  if (install_file(param_path, param_json, param_json_size)) {
    wkali_log("[WKALI] Failed to install param.json\n");
    sceAppInstUtilTerminate();
    return -1;
  }

  if (install_file(icon_path, icon0_png, icon0_png_size)) {
    wkali_log("[WKALI] Failed to install icon0.png\n");
    sceAppInstUtilTerminate();
    return -1;
  }

  /* pic0 = home focus background (what was missing). */
  if (install_file(pic0_path, pic0_png, pic0_png_size)) {
    wkali_log("[WKALI] Failed to install pic0.png (focus background)\n");
    sceAppInstUtilTerminate();
    return -1;
  }

  if (install_file(pic1_path, pic0_png, pic0_png_size)) {
    wkali_log("[WKALI] Failed to install pic1.png\n");
    sceAppInstUtilTerminate();
    return -1;
  }

  mirror_appmeta(title_id);

  if ((err = install_app(title_id, "/user/app/"))) {
    wkali_log("[WKALI] install_app: error 0x%08X\n", err);
    sceAppInstUtilTerminate();
    return -1;
  }

  /* Registration can refresh appmeta — write focus art again last. */
  mirror_appmeta(title_id);

  wkali_log("[WKALI] Launcher app installed successfully.\n");
  wkali_notify("WebKit Autoloader App Ready!");

  sceAppInstUtilTerminate();
  return 0;
}
