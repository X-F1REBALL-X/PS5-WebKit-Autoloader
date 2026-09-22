## WK Autoloader

Jailbreak from the PS5 homescreen.

**Download:** [Releases](https://github.com/X-F1REBALL-X/WK-Autoloader/releases)

## Firmwares

| Firmware | Status |
| --- | --- |
| **1.00 – 5.50** | Works |
| **6.xx** | No |
| **7.00 – 12.00** | Works |
| **12.02 – 12.70** | Works |
| **13.xx** | No (offsets only) |

## Install

### Via sjb (9.00 – 12.00 only)

[sjb](https://x-f1reball-x.github.io/sjb/) ([repo](https://github.com/X-F1REBALL-X/sjb)) works only on **9.00 – 12.00**.

On those firmwares, sjb opens Payload Manager first, then installs WK Autoloader.

If Payload Manager **auto-open page** is on, Autoloader will not install. Turn that off and jailbreak again from sjb, **or** send `webkit-autoloader-installer.elf` from Payload Manager.

### Manual install (any supported firmware)

1. Download the `.elf` from [Releases](https://github.com/X-F1REBALL-X/WK-Autoloader/releases)
2. Send it to the ELF loader
3. Open the homescreen app and run the jailbreak

## How it works

Detects your console and firmware version, then runs the matching jailbreak chain.

## Offline

No internet needed to jailbreak with WK Autoloader. It runs from the homescreen after install.

## Credits

With respect to the people behind the bugs and chains this app uses:

- **Synacktiv** — UMTX kernel bug (CVE-2024-43102)
- **fail0verflow** / **flatz** — UMTX exploit strategy
- **TheFloW** — ExploitNetControlImpl (poops base)
- **Gezine** / **egycnq** — poops; **Gezine** — p2jb
- **abc** — PSFree (WebKit userland)
- **shahrilnet** / **n0llptr** — UMTX Lua implementation
- **SpecterDev** / **ChendoChap** — UMTX WebKit jailbreak work
- **idlesauce** — umtx2
- **cheburek3000** — p2jb Lua port
- **Sonic** — pooP2JB
- **jordyidk** — slopkit
- **ufm42** — kexp
- **John Tornblom** — ELF loader / payloads
- **zecoxao** — support
- **Yenyen** — support
- **EchoStretch** — support
- **PS5 R&D Discord** — support


## Notes

- Keep only the current Release on GitHub.
- Short English release notes (for example: System fixes).
