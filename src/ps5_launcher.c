#include <ps5/kernel.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "wkali.h"
#include "ps5_launcher.h"

extern int sceSystemServiceLaunchWebBrowser(const char *uri);
extern int sceKernelLoadStartModule(const char *path, size_t args, const void *argp,
                                    uint32_t flags, const void *pOpt, int *pRes);
extern int sceUserServiceGetForegroundUser(int *userId);
extern int sceUserServiceGetInitialUser(int *userId);

typedef struct {
    unsigned int size;
    uint32_t userId;
} SceShellUIUtilLaunchByUriParam;

int ps5_launch_browser(const char *uri) {
  wkali_log("[WKALI] Launching browser: %s\n", uri);
  if (sceSystemServiceLaunchWebBrowser(uri) != 0) {
    wkali_notify("WKALI: Failed to launch browser.");
    return -1;
  }
  return 0;
}

/* Same approach as ps5-unified-autoloader: navigate home via ShellUIUtil so
 * SceNKWebProcess closes without an OS error dialog. */
int ps5_return_to_home(void) {
  int (*p_init)(void) = NULL;
  int (*p_launch)(const char *uri, SceShellUIUtilLaunchByUriParam *param) = NULL;

  int mod = sceKernelLoadStartModule(
      "/system_ex/common_ex/lib/libSceShellUIUtil.sprx", 0, 0, 0, 0, 0);
  if (mod < 0) {
    wkali_log("[WKALI] ShellUIUtil load failed: 0x%08x\n", mod);
    return -1;
  }

  p_init = (void *)kernel_dynlib_dlsym(-1, (uint32_t)mod, "sceShellUIUtilInitialize");
  p_launch = (void *)kernel_dynlib_dlsym(-1, (uint32_t)mod, "sceShellUIUtilLaunchByUri");
  if (!p_init || !p_launch) {
    wkali_log("[WKALI] ShellUIUtil symbols missing\n");
    return -1;
  }

  SceShellUIUtilLaunchByUriParam param;
  memset(&param, 0, sizeof(param));
  param.size = sizeof(param);

  p_init();

  if (sceUserServiceGetForegroundUser((int *)&param.userId) != 0 ||
      param.userId == 0 || param.userId == (uint32_t)-1) {
    sceUserServiceGetInitialUser((int *)&param.userId);
  }

  wkali_log("[WKALI] Returning to home (close browser), userId=0x%08x\n",
            param.userId);
  int res = p_launch("pshomeui:navigateToHome?bootCondition=psButton", &param);
  if (res != 0) {
    wkali_log("[WKALI] navigateToHome failed: 0x%08x\n", res);
  }
  return res;
}
