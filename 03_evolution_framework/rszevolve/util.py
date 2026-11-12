"""Small shared helpers: subprocess with timeout + captured log, JSON I/O, timestamps, logging."""
from __future__ import annotations

import json
import os
import signal
import subprocess
import sys
import time
from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Iterable


def now_iso() -> str:
    return datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


def stamp() -> str:
    return datetime.now().strftime("%Y%m%d_%H%M%S")


def log(msg: str, *, prefix: str = "rszevolve") -> None:
    print(f"[{prefix}] {msg}", flush=True)


def read_json(p: Path, default: Any = None) -> Any:
    try:
        return json.loads(Path(p).read_text())
    except FileNotFoundError:
        return default


def write_json(p: Path, data: Any) -> None:
    p = Path(p)
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text(json.dumps(data, indent=2, sort_keys=False, default=str) + "\n")


def write_text(p: Path, text: str) -> None:
    p = Path(p)
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text(text)


@dataclass
class RunResult:
    cmd: list[str]
    returncode: int
    stdout: str
    seconds: float
    timed_out: bool = False

    @property
    def ok(self) -> bool:
        return self.returncode == 0 and not self.timed_out


def run(cmd: Iterable[str], *, cwd: Path | None = None, env: dict[str, str] | None = None,
        timeout: int | None = None, log_file: Path | None = None, echo: bool = False) -> RunResult:
    """Run a command in its own process group, capture combined output, kill the whole group on timeout."""
    cmd = [str(c) for c in cmd]
    merged = dict(os.environ)
    if env:
        merged.update({k: str(v) for k, v in env.items()})
    t0 = time.time()
    chunks: list[str] = []
    fh = open(log_file, "w") if log_file else None
    try:
        proc = subprocess.Popen(cmd, cwd=str(cwd) if cwd else None, env=merged, stdout=subprocess.PIPE,
                                stderr=subprocess.STDOUT, text=True, start_new_session=True, bufsize=1)
        timed_out = False
        try:
            assert proc.stdout is not None
            deadline = time.time() + timeout if timeout else None
            for line in proc.stdout:
                chunks.append(line)
                if fh:
                    fh.write(line); fh.flush()
                if echo:
                    sys.stdout.write(line); sys.stdout.flush()
                if deadline and time.time() > deadline:
                    raise subprocess.TimeoutExpired(cmd, timeout)
            proc.wait(timeout=max(1, (deadline - time.time())) if deadline else None)
        except subprocess.TimeoutExpired:
            timed_out = True
            try:
                os.killpg(proc.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
            proc.wait()
        return RunResult(cmd, proc.returncode if not timed_out else -9, "".join(chunks), time.time() - t0, timed_out)
    finally:
        if fh:
            fh.close()


def tail(text: str, n: int = 60) -> str:
    lines = text.splitlines()
    return "\n".join(lines[-n:])


def grep_lines(text: str, needles: Iterable[str], limit: int = 80) -> list[str]:
    out = []
    for line in text.splitlines():
        if any(n in line for n in needles):
            out.append(line)
            if len(out) >= limit:
                break
    return out


def fmt_ns(x: float | None) -> str:
    return "n/a" if x is None else f"{x:+.4f}"
