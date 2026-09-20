# Public firmware offset profiles (research / userland)

These files are **copied** from public repositories for WebKit userland
offset tables. They are **not** a jailbreak chain.

## Layout

| File | Firmware | Primary source |
| --- | --- | --- |
| `13.xx/13.00.js` | 13.00 | [badrcoderman/bwslop](https://github.com/badrcoderman/bwslop) `offsets/13.00.js` |
| `13.xx/13.20.js` | 13.20 | [badrcoderman/bwslop](https://github.com/badrcoderman/bwslop) `offsets/13.20.js` |
| `13.xx/13.40.js` | 13.40 | [Wamphyre/PSAITO](https://github.com/Wamphyre/PSAITO) `offsets/13.XX/13.40` |
| `13.xx/13.60.js` | 13.60 | [badrcoderman/bwslop](https://github.com/badrcoderman/bwslop) `offsets/13.60.js` (cross-credits X1NON / PSAITO in-file) |

Related public trees also consulted (not copied wholesale):
[X1NONs/X1NON-PSJB](https://github.com/X1NONs/X1NON-PSJB) `offsets/13.XX/*`.

## How they land in the Autoloader build

`third_party/slopkit` stays a **pristine** submodule.  
`tools/apply_slopkit_patch.sh` (Makefile `slopkit-prepare`) overlays
`13.xx/*.js` into `frontend/autoloader/slopkit/offsets/` after the
submodule copy. That frontend tree is gitignored and regenerated.

## Status

Offsets only. **No public kernel exploit** for 13.00–13.60 as of the
research date documented in the Autoloader README. Do not treat presence
of these files as a working full jailbreak.

## Not found (distinct public flat profiles)

- Authentic distinct `13.42.js` / `13.50.js` / `13.52.js` matching the
  slopkit flat offset format (some forks had mislabeled 13.60 copies).
