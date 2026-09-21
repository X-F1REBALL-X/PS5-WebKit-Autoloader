#!/usr/bin/env python3
"""Insert a settle delay after elfldr accepts, before sending payload.elf."""
import re
import sys
from pathlib import Path

SETTLE = (
    "    // Let elfldr settle before sending payload.elf "
    "(avoids panic on Payload Manager).\n"
    "    await new Promise(function (resolve) { setTimeout(resolve, 3000); });\n"
)

def patch_file(path: Path) -> bool:
    t = path.read_text()
    if "avoids panic on Payload Manager" in t:
        print(f"already settled: {path}")
        return False
    new, n = re.subn(
        r"(    if \(!ready\) \{[\s\S]*?return;\n    \}\n)"
        r"(    sendPayloadToElfldr\((?:AUTOLOAD|cfg\.autoload))",
        r"\1" + SETTLE + r"\2",
        t,
        count=1,
    )
    if n != 1:
        new, n = re.subn(
            r"(\n)(    sendPayloadToElfldr\((?:AUTOLOAD|cfg\.autoload))",
            r"\1" + SETTLE + r"\2",
            t,
            count=1,
        )
    if n != 1:
        print(f"WARN: could not settle {path}", file=sys.stderr)
        return False
    path.write_text(new)
    print(f"settled: {path}")
    return True

def main():
    root = Path(sys.argv[1] if len(sys.argv) > 1 else ".")
    for name in ("poops.html", "p2jb.html"):
        paths = [root / name] if (root / name).is_file() else list(root.rglob(name))
        for path in paths:
            # only the autoloader slopkit copies
            patch_file(path)

if __name__ == "__main__":
    main()
