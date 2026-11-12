"""Headless Claude Code runner.

Every agent call is `claude -p <prompt> --output-format json ...` executed in a chosen working
directory with an explicit tool allow-list and extra readable directories. The JSON result carries
`result` (final text), `usage`, `total_cost_usd`, `session_id`, `num_turns`, `is_error`.

Prompt, raw JSON and the final text are written next to each other under 11_agent_data/<iter>/
so every agent interaction can be inspected later."""
from __future__ import annotations

import json
import os
import shlex
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

from ..config import PATHS
from ..util import log, run, write_text

READ_TOOLS = ["Read", "Grep", "Glob", "LS"]
EDIT_TOOLS = READ_TOOLS + ["Edit", "Write", "MultiEdit"]


@dataclass
class AgentCall:
    role: str                       # planner | coder:<cluster> | evaluator | context:<what>
    prompt: str
    cwd: Path
    model: str
    max_turns: int
    allowed_tools: list[str] = field(default_factory=lambda: list(READ_TOOLS))
    add_dirs: list[Path] = field(default_factory=list)
    system_prompt_file: Path | None = None
    resume_session: str | None = None
    max_budget_usd: float | None = None
    timeout_s: int = 3600
    bash_allow: list[str] = field(default_factory=list)   # e.g. ["Bash(bazelisk build *)"]


@dataclass
class AgentResult:
    text: str
    raw: dict[str, Any]
    returncode: int
    seconds: float
    session_id: str | None

    @property
    def ok(self) -> bool:
        return self.returncode == 0 and not self.raw.get("is_error", False)


def _claude_env() -> dict[str, str]:
    env = {}
    # Keep the subprocess from inheriting a nested-session marker that makes `claude -p` refuse to run.
    for k in ("CLAUDECODE", "CLAUDE_CODE_ENTRYPOINT"):
        env[k] = ""
    return env


def run_agent(call: AgentCall, *, log_dir: Path, tag: str) -> AgentResult:
    """Execute one headless Claude session. Files written: <tag>.prompt.md, <tag>.raw.json, <tag>.txt, <tag>.cmd"""
    log_dir.mkdir(parents=True, exist_ok=True)
    write_text(log_dir / f"{tag}.prompt.md", call.prompt)
    cmd = [PATHS.claude_bin, "-p", "--output-format", "json", "--model", call.model,
           "--max-turns", str(call.max_turns), "--permission-mode", "acceptEdits"]
    tools = list(call.allowed_tools) + list(call.bash_allow)
    if tools:
        cmd += ["--allowedTools", *tools]
    for d in call.add_dirs:
        cmd += ["--add-dir", str(d)]
    if call.system_prompt_file:
        cmd += ["--append-system-prompt-file", str(call.system_prompt_file)]
    if call.resume_session:
        cmd += ["--resume", call.resume_session]
    if call.max_budget_usd:
        cmd += ["--max-budget-usd", f"{call.max_budget_usd:.2f}"]
    write_text(log_dir / f"{tag}.cmd", " ".join(shlex.quote(c) for c in cmd) + f"\n# cwd={call.cwd}\n")
    log(f"{call.role}: claude -p (model={call.model}, max_turns={call.max_turns}, cwd={call.cwd.name})")
    # prompt goes on stdin to avoid argv length limits
    env = _claude_env()
    import subprocess, time, signal
    t0 = time.time()
    proc = subprocess.Popen(cmd, cwd=str(call.cwd), env={**os.environ, **env}, stdin=subprocess.PIPE,
                            stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, start_new_session=True)
    try:
        out, err = proc.communicate(call.prompt, timeout=call.timeout_s)
        rc = proc.returncode
    except subprocess.TimeoutExpired:
        os.killpg(proc.pid, signal.SIGKILL)
        out, err = proc.communicate()
        rc = -9
        err = (err or "") + "\n[rszevolve] agent timed out"
    secs = time.time() - t0
    raw: dict[str, Any] = {}
    try:
        raw = json.loads(out) if out.strip() else {}
    except json.JSONDecodeError:
        # stream or partial output: keep the last JSON object we can find
        for line in reversed(out.splitlines()):
            try:
                raw = json.loads(line); break
            except json.JSONDecodeError:
                continue
    if not raw:
        raw = {"is_error": True, "result": "", "stderr": err[-4000:], "stdout_tail": out[-2000:]}
    else:
        raw["stderr_tail"] = (err or "")[-2000:]
    write_text(log_dir / f"{tag}.raw.json", json.dumps(raw, indent=2))
    text = str(raw.get("result") or "")
    write_text(log_dir / f"{tag}.txt", text)
    res = AgentResult(text=text, raw=raw, returncode=rc, seconds=secs, session_id=raw.get("session_id"))
    log(f"{call.role}: done in {secs:.0f}s, turns={raw.get('num_turns')}, cost=${float(raw.get('total_cost_usd') or 0):.3f}, ok={res.ok}")
    if not res.ok:
        log(f"{call.role}: stderr tail: {(raw.get('stderr') or raw.get('stderr_tail') or '')[-600:]}")
    return res


def extract_json_block(text: str) -> dict[str, Any] | None:
    """Agents are asked to end with a ```json block; pull the last one out."""
    import re
    blocks = re.findall(r"```json\s*(\{.*?\})\s*```", text, flags=re.S)
    for b in reversed(blocks):
        try:
            return json.loads(b)
        except json.JSONDecodeError:
            continue
    # fall back: last {...} in the text
    m = re.findall(r"(\{(?:[^{}]|\{[^{}]*\})*\})", text, flags=re.S)
    for b in reversed(m):
        try:
            return json.loads(b)
        except json.JSONDecodeError:
            continue
    return None
