"""Build a candidate rsz tree into build/bin/openroad_evolved via tools/build_openroad.sh (Bazel overlay).

Returns a BuildResult with the compiler diagnostics extracted from the Bazel log so the coding agent can
fix its own errors. The pristine rsz is restored into external/OpenROAD/src/rsz afterwards by the script."""
from __future__ import annotations

import re
from dataclasses import dataclass, field
from pathlib import Path

from ..config import PATHS, Knobs
from ..util import log, run, tail

ERR_RE = re.compile(r"^(?:.*?/)?(src/rsz/[^:]+):(\d+):(\d+): (error|warning): (.*)$")


@dataclass
class BuildResult:
    ok: bool
    binary: Path
    seconds: float
    log_path: Path
    errors: list[str] = field(default_factory=list)      # "src/rsz/src/X.cc:12:5: error: ..."
    warnings: list[str] = field(default_factory=list)
    log_tail: str = ""

    def diagnostics(self, limit: int = 40) -> str:
        parts = []
        if self.errors:
            parts.append("Compiler errors:\n" + "\n".join(self.errors[:limit]))
        if not self.errors and not self.ok:
            parts.append("Build failed without a parsed compiler error. Bazel log tail:\n" + self.log_tail)
        if self.warnings:
            parts.append(f"Warnings ({len(self.warnings)}):\n" + "\n".join(self.warnings[:15]))
        return "\n\n".join(parts) if parts else "build ok, no diagnostics"


def _parse(text: str) -> tuple[list[str], list[str]]:
    errs, warns = [], []
    seen: set[str] = set()
    lines = text.splitlines()
    for i, line in enumerate(lines):
        m = ERR_RE.match(line.strip())
        if not m:
            continue
        key = line.strip()
        if key in seen:
            continue
        seen.add(key)
        # include up to 3 context lines (the source excerpt and caret) for the agent
        ctx = "\n".join(l for l in lines[i + 1:i + 4] if l and not ERR_RE.match(l.strip()) and not l.startswith("["))
        entry = f"{m.group(1)}:{m.group(2)}:{m.group(3)}: {m.group(4)}: {m.group(5)}" + (f"\n    {ctx.strip()}" if ctx.strip() else "")
        (errs if m.group(4) == "error" else warns).append(entry)
    # link errors / undefined symbols
    for line in lines:
        if "undefined symbol" in line.lower() or "undefined reference" in line.lower() or "duplicate symbol" in line.lower():
            if line.strip() not in seen:
                seen.add(line.strip()); errs.append(line.strip())
    return errs, warns


def build_candidate(rsz_dir: Path, knobs: Knobs, *, tag: str = "candidate") -> BuildResult:
    rsz_dir = Path(rsz_dir).resolve()
    if not (rsz_dir / "src").is_dir():
        raise FileNotFoundError(f"{rsz_dir} is not an rsz tree (no src/)")
    script = PATHS.tools / "build_openroad.sh"
    log(f"build[{tag}]: overlay {rsz_dir.relative_to(PATHS.root) if rsz_dir.is_relative_to(PATHS.root) else rsz_dir} and bazelisk build //:openroad")
    res = run([script, "evolved", rsz_dir], timeout=knobs.build_timeout_s)
    # the script writes its own full log under build/logs; find the newest
    logs = sorted((PATHS.build / "logs").glob("build_evolved_*.log"))
    log_path = logs[-1] if logs else PATHS.build / "logs" / "missing.log"
    full = log_path.read_text() if log_path.exists() else res.stdout
    errs, warns = _parse(full)
    ok = res.ok and PATHS.openroad_evolved.exists() and "Build completed successfully" in full
    br = BuildResult(ok, PATHS.openroad_evolved, res.seconds, log_path, errs, warns, tail(full, 40))
    log(f"build[{tag}]: {'ok' if ok else 'FAILED'} in {res.seconds:.0f}s, {len(errs)} errors, {len(warns)} warnings")
    return br


def build_stock(knobs: Knobs) -> BuildResult:
    res = run([PATHS.tools / "build_openroad.sh", "stock"], timeout=knobs.build_timeout_s)
    logs = sorted((PATHS.build / "logs").glob("build_stock_*.log"))
    log_path = logs[-1] if logs else PATHS.build / "logs" / "missing.log"
    full = log_path.read_text() if log_path.exists() else res.stdout
    errs, warns = _parse(full)
    return BuildResult(res.ok and PATHS.openroad_stock.exists(), PATHS.openroad_stock, res.seconds, log_path, errs, warns, tail(full, 40))
