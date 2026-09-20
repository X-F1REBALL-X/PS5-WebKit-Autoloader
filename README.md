# PS5-WebKit-Autoloader

Homescreen WebKit jailbreak launcher for PS5.

**Created by X-F1REBALL-X**

Homescreen app title: **PS5-WebKit-Autoloader v1**

Companion host: [SLOPKIT-PS5](https://github.com/X-F1REBALL-X/SLOPKIT-PS5)

## Supported firmwares

| Firmware | Exploit chain |
| --- | --- |
| **1.00 – 5.50** | umtx2 |
| **7.00 – 12.00** | poops (slopkit) |
| **12.02 – 12.70** | p2jb |

`6.xx` is **not** supported.

The app picks the chain automatically from the PS5 firmware in the browser user-agent. This project is **not** slopkit-only — it bundles umtx2, slopkit/poops, and p2jb.

## Setup

1. Jailbreak once with [SLOPKIT-PS5](https://x-f1reball-x.github.io/SLOPKIT-PS5/).
2. Send `webkit-autoloader-installer_v1.elf` from [Releases](https://github.com/X-F1REBALL-X/PS5-WebKit-Autoloader/releases/tag/v1) (or let SLOPKIT-PS5 auto-send it).
3. Reboot once.
4. Open **PS5-WebKit-Autoloader v1** from the homescreen.

## Build

```bash
BUILD_TYPE=stable make all
```

Homescreen title uses `WKAL_VERSION` in `include/wkali.h` (currently `1`).

## Credits

- **Created by:** X-F1REBALL-X
- **Host UI / branding:** X-F1REBALL-X
- **Exploit / chain:** TheFloW · Gezine · WhiteShadow · ufm42 · Nathan Fargo · Dr.Yenyen · ArabPixel · MasterMaind · ABC · raw13g · Echo Stretch · idlesauce · jordyidk · scene contributors
- **License:** see `LICENSE` (GPL)
