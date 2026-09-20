# PS5-WebKit-Autoloader

Homescreen WebKit jailbreak launcher for PS5.

**Created by X-F1REBALL-X**

- **Repo:** [X-F1REBALL-X/PS5-WebKit-Autoloader](https://github.com/X-F1REBALL-X/PS5-WebKit-Autoloader)
- **Release:** [v1](https://github.com/X-F1REBALL-X/PS5-WebKit-Autoloader/releases/tag/v1)
- **Homescreen app title:** PS5-WebKit-Autoloader v1
- **Companion host:** [SLOPKIT-PS5](https://github.com/X-F1REBALL-X/SLOPKIT-PS5) · live: https://x-f1reball-x.github.io/SLOPKIT-PS5/

## Supported firmwares

| Firmware | Exploit chain |
| --- | --- |
| **1.00 – 5.50** | umtx2 |
| **7.00 – 12.00** | poops (slopkit) |
| **12.02 – 12.70** | p2jb |

`6.xx` is **not** supported.

The app picks the chain automatically from the PS5 firmware in the browser user-agent. This project is **not** slopkit-only — it bundles umtx2, slopkit/poops, and p2jb.

## UI features

- Logo (WK) above the title
- Title: **PS5-WebKit-Autoloader** with a small badge
- Live **firmware + chain** line (example: `FW 9.00 · chain poops`)
- Status: **Jailbreak started**
- Progress bar with live **%** and a soft blue glow
- **Elapsed** timer (example: `Elapsed 0:13`)
- Success: **✓ Jailbreak completed successfully**
- Failure (red): **Jailbreak failed - restart your console**
- Footer: **Created by X-F1REBALL-X**

## Setup

1. On the PS5, open the browser and go to:  
   https://x-f1reball-x.github.io/SLOPKIT-PS5/
2. Wait until the jailbreak finishes (**Jailbreak completed successfully**).
3. The host auto-sends **Payload Manager**, then **webkit-autoloader-installer**.
4. When the installer page opens, leave it open until it says the homescreen shortcut is ready, then close it.
5. **Reboot the PS5 once.**
6. Open **PS5-WebKit-Autoloader v1** from the homescreen.

### Updating

After a new installer build (UI / icon / name changes), run the jailbreak host again so it auto-sends the new installer, let it finish, then reboot once so the homescreen app and cache refresh.

## Build

```bash
BUILD_TYPE=stable make all
```

Homescreen title version comes from `WKAL_VERSION` in `include/wkali.h` (currently `1`). Use `BUILD_TYPE=stable` for a clean `v1` label (no `-dev-…` suffix).

## Credits

- **Created by:** X-F1REBALL-X
- **Host UI / branding:** X-F1REBALL-X
- **Exploit / chain:** TheFloW · Gezine · ufm42 · Nathan Fargo · Dr.Yenyen · ArabPixel · ABC · Echo Stretch · idlesauce · jordyidk · scene contributors
- **License:** see `LICENSE` (GPL)
