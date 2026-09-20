# PS5-WebKit-Autoloader

Homescreen WebKit jailbreak launcher for PS5.

**Created by X-F1REBALL-X**

**Release:** [v1](https://github.com/X-F1REBALL-X/PS5-WebKit-Autoloader/releases/tag/v1)

## Supported firmwares

| Firmware | Status | Exploit chain |
| --- | --- | --- |
| **1.00 – 5.50** | Full JB | umtx2 |
| **6.xx** | **Not supported** | No WebKit + kernel combo in this Autoloader |
| **7.00 – 12.00** | Full JB | poops (slopkit) |
| **12.02 – 12.70** | Full JB | p2jb |
| **13.00 / 13.20 / 13.40 / 13.60** | **Offsets / userland only** | Public WebKit offset profiles shipped for research; **no public kernel exploit** — Autoloader will **not** auto-run a full JB chain |

`6.xx` remains unsupported for this WebKit Autoloader.

**Important:** Presence of `13.xx` offset files does **not** mean a working jailbreak. As of 2026-09-21 there is no public end-to-end kernel exploit for firmware 13.00–13.60. The UI detects those firmwares and shows a clear “userland only” refusal.

Offset files live in `third_party/public-offsets/13.xx/` and are overlaid into the regenerated `frontend/autoloader/slopkit/offsets/` tree by `tools/apply_slopkit_patch.sh` (Makefile `slopkit-prepare`). The `third_party/slopkit` submodule stays pristine.

## Setup

1. On the PS5 browser open: https://x-f1reball-x.github.io/SLOPKIT-PS5/
2. Wait for **Jailbreak completed successfully**.
3. Leave the installer open until the homescreen shortcut is ready.
4. **Reboot once.**
5. Open **PS5-WebKit-Autoloader v1** from the homescreen.

## Credits

- **Created by:** X-F1REBALL-X
- **Exploit / chain:** TheFloW · Gezine · ufm42 · Nathan Fargo · Dr.Yenyen · ArabPixel · ABC · Echo Stretch · idlesauce · jordyidk · scene contributors
- **13.xx WebKit offset profiles (public, research / userland):**
  - [badrcoderman/bwslop](https://github.com/badrcoderman/bwslop) — `offsets/13.00.js`, `13.20.js`, `13.60.js`
  - [Wamphyre/PSAITO](https://github.com/Wamphyre/PSAITO) — `offsets/13.XX/13.40` (and related 13.xx toolkit)
  - [X1NONs/X1NON-PSJB](https://github.com/X1NONs/X1NON-PSJB) — `offsets/13.XX/*` (cross-reference)
- **License:** see `LICENSE` (GPL)
