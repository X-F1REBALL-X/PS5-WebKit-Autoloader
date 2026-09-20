# PS5-WebKit-Autoloader

Homescreen WebKit jailbreak launcher for PS5.

- **Repo:** [X-F1REBALL-X/PS5-WebKit-Autoloader](https://github.com/X-F1REBALL-X/PS5-WebKit-Autoloader)
- **Release:** [v1](https://github.com/X-F1REBALL-X/PS5-WebKit-Autoloader/releases/tag/v1)
- **Companion host:** [SLOPKIT-PS5](https://github.com/X-F1REBALL-X/SLOPKIT-PS5) · live: https://x-f1reball-x.github.io/SLOPKIT-PS5/

## Supported firmwares

| Firmware | Exploit chain |
| --- | --- |
| **1.00 – 5.50** | umtx2 |
| **7.00 – 12.00** | poops (slopkit) |
| **12.02 – 12.70** | p2jb |

`6.xx` is **not** supported.

The app picks the chain automatically from the PS5 firmware in the browser user-agent. This project is **not** slopkit-only — it bundles umtx2, slopkit/poops, and p2jb.

## UI feature
- Live **firmware + chain** line (example: `FW 9.00 · chain poops`)
- Status: **Jailbreak started**
- Progress bar with live **%** and a soft blue glow
- **Elapsed** timer (example: `Elapsed 0:13`)
- Success: **✓ Jailbreak completed successfully**
- Failure (red): **Jailbreak failed - restart your console**

## Setup

1. Jailbreak once with [SLOPKIT-PS5](https://x-f1reball-x.github.io/SLOPKIT-PS5/).
2. Send `webkit-autoloader-installer_v1.elf` from [Releases](https://github.com/X-F1REBALL-X/PS5-WebKit-Autoloader/releases/tag/v1)  
   (or let SLOPKIT-PS5 auto-send Payload Manager, then this installer).
3. Reboot once.
4. Open **PS5-WebKit-Autoloader v1** from the homescreen.

After you update the installer, run it again once so the homescreen app and cached UI refresh.

## Build

```bash
BUILD_TYPE=stable make all
```

Homescreen title version comes from `WKAL_VERSION` in `include/wkali.h` (currently `1`). Use `BUILD_TYPE=stable` for a clean `v1` label (no `-dev-…` suffix).

## Credits

- **Created by:** X-F1REBALL-X
- **Exploit / chain:** TheFloW · Gezine · ufm42 · Nathan Fargo · Dr.Yenyen · ArabPixel · ABC · Echo Stretch · idlesauce · jordyidk · scene contributors
- **License:** see `LICENSE` (GPL)
