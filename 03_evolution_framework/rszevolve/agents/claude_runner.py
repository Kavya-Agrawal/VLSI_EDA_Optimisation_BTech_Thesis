"""Audited headless-agent runner with provider fallback.

The historical module name is kept so existing imports remain stable. Required calls try the provider chain from
``AGENT_PROVIDERS`` (default: Claude -> Codex GPT -> Antigravity Gemini). Each CLI uses its own existing login;
credentials are neither read nor copied by this framework.

Every attempt is recorded under ``11_agent_data`` as ``<tag>.<provider>.*``. The provider that ultimately supplies
the result is also written to the canonical ``<tag>.*`` files consumed by the budget and orchestration code.
Fallback is deliberately narrow: it occurs for availability failures (limits, rate limiting, authentication,
network/service failure, timeout, or missing executable), never for a successful agent whose proposed code later
fails to build or evaluate.
"""
from __future__ import annotations

import json
import os
import shlex
import signal
import subprocess
import time
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

from ..config import PATHS
from ..util import log, write_text

READ_TOOLS = ["Read", "Grep", "Glob", "LS"]
EDIT_TOOLS = READ_TOOLS + ["Edit", "Write", "MultiEdit"]
KNOWN_PROVIDERS = ("claude", "codex", "antigravity")


@dataclass
class AgentCall:
    role: str
    prompt: str
    cwd: Path
    model: str                         # Claude model; fallback models are selected by environment.
    max_turns: int
    allowed_tools: list[str] = field(default_factory=lambda: list(READ_TOOLS))
    add_dirs: list[Path] = field(default_factory=list)
    system_prompt_file: Path | None = None
    resume_session: str | None = None
    max_budget_usd: float | None = None
    timeout_s: int = 3600
    bash_allow: list[str] = field(default_factory=list)


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


@dataclass
class _Attempt:
    provider: str
    raw: dict[str, Any]
    returncode: int
    seconds: float
    command: list[str]


def _provider_order(call: AgentCall) -> list[str]:
    configured = [p.strip().lower() for p in os.environ.get("AGENT_PROVIDERS", ",".join(KNOWN_PROVIDERS)).split(",")]
    providers = [p for p in configured if p in KNOWN_PROVIDERS]
    if not providers:
        providers = list(KNOWN_PROVIDERS)
    if call.resume_session and ":" in call.resume_session:
        current = call.resume_session.split(":", 1)[0]
        if current in providers:
            providers = [current] + [p for p in providers if p != current]
    return providers


def _session_for(call: AgentCall, provider: str) -> str | None:
    session = call.resume_session
    if not session:
        return None
    if ":" not in session:
        return session if provider == "claude" else None  # compatibility with old Claude-only logs
    owner, value = session.split(":", 1)
    return value if owner == provider else None


def _model_for(call: AgentCall, provider: str) -> str:
    if provider == "claude":
        return call.model
    if provider == "codex":
        return os.environ.get("CODEX_AGENT_MODEL", "gpt-6.1-sol")
    return os.environ.get("ANTIGRAVITY_AGENT_MODEL", "gemini-3.8-flash-high")


def _editable(call: AgentCall) -> bool:
    return any(tool in call.allowed_tools for tool in ("Edit", "Write", "MultiEdit"))


def _base_env(provider: str) -> dict[str, str]:
    env = dict(os.environ)
    if provider == "claude":
        for key in ("CLAUDECODE", "CLAUDE_CODE_ENTRYPOINT"):
            env[key] = ""
    elif provider == "codex":
        # Do not make a child Codex attach to a parent thread or inherit a parent sandbox/network restriction.
        for key in tuple(env):
            if key.startswith("CODEX_") and key != "CODEX_HOME":
                env.pop(key, None)
    return env


def _run_process(cmd: list[str], call: AgentCall, provider: str, *, stdin_text: str | None) -> tuple[str, str, int, float]:
    t0 = time.time()
    try:
        proc = subprocess.Popen(cmd, cwd=str(call.cwd), env=_base_env(provider),
                                stdin=subprocess.PIPE if stdin_text is not None else subprocess.DEVNULL,
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, start_new_session=True)
    except (FileNotFoundError, PermissionError, OSError) as exc:
        return "", str(exc), 127, time.time() - t0
    try:
        out, err = proc.communicate(stdin_text, timeout=call.timeout_s)
        return out, err, int(proc.returncode or 0), time.time() - t0
    except subprocess.TimeoutExpired:
        os.killpg(proc.pid, signal.SIGKILL)
        out, err = proc.communicate()
        return out, (err or "") + f"\n[rszevolve] {provider} agent timed out", -9, time.time() - t0


def _last_json_object(text: str) -> dict[str, Any]:
    try:
        value = json.loads(text)
        return value if isinstance(value, dict) else {}
    except json.JSONDecodeError:
        pass
    for line in reversed(text.splitlines()):
        try:
            value = json.loads(line)
            if isinstance(value, dict):
                return value
        except json.JSONDecodeError:
            continue
    return {}


def _run_claude(call: AgentCall) -> _Attempt:
    cmd = [PATHS.claude_bin, "-p", "--output-format", "json", "--model", _model_for(call, "claude"),
           "--max-turns", str(call.max_turns), "--permission-mode", "acceptEdits"]
    tools = list(call.allowed_tools) + list(call.bash_allow)
    if tools:
        cmd += ["--allowedTools", *tools]
    for directory in call.add_dirs:
        cmd += ["--add-dir", str(directory)]
    if call.system_prompt_file:
        cmd += ["--append-system-prompt-file", str(call.system_prompt_file)]
    if session := _session_for(call, "claude"):
        cmd += ["--resume", session]
    if call.max_budget_usd:
        cmd += ["--max-budget-usd", f"{call.max_budget_usd:.2f}"]
    out, err, rc, secs = _run_process(cmd, call, "claude", stdin_text=call.prompt)
    raw = _last_json_object(out)
    if not raw:
        raw = {"is_error": True, "result": "", "stderr": err[-4000:], "stdout_tail": out[-2000:]}
    raw["stderr_tail"] = (err or "")[-2000:]
    raw.setdefault("is_error", rc != 0)
    raw.setdefault("total_cost_usd", 0)
    return _Attempt("claude", raw, rc, secs, cmd)


def _parse_codex(out: str, err: str, rc: int) -> dict[str, Any]:
    events: list[dict[str, Any]] = []
    for line in out.splitlines():
        try:
            value = json.loads(line)
            if isinstance(value, dict):
                events.append(value)
        except json.JSONDecodeError:
            continue
    thread_id = next((event.get("thread_id") for event in events if event.get("type") == "thread.started"), None)
    messages = [event.get("item", {}).get("text", "") for event in events
                if event.get("type") == "item.completed" and event.get("item", {}).get("type") == "agent_message"]
    completed = [event for event in events if event.get("type") == "turn.completed"]
    usage = completed[-1].get("usage", {}) if completed else {}
    failures = [event for event in events if event.get("type") in ("error", "turn.failed")]
    failure_text = "\n".join(str(event.get("message") or event.get("error") or event) for event in failures)
    result = messages[-1] if messages else ""
    is_error = rc != 0 or bool(failures) or not result.strip()
    return {"type": "result", "subtype": "success" if not is_error else "error", "is_error": is_error,
            "result": result, "session_id": thread_id, "num_turns": len(completed), "total_cost_usd": 0,
            "usage": {"input_tokens": int(usage.get("input_tokens", 0) or 0),
                      "output_tokens": int(usage.get("output_tokens", 0) or 0),
                      "cache_read_input_tokens": int(usage.get("cached_input_tokens", 0) or 0)},
            "api_error": failure_text, "stderr_tail": (err or "")[-2000:], "stdout_tail": out[-2000:]}


def _run_codex(call: AgentCall) -> _Attempt:
    sandbox = "workspace-write" if _editable(call) else "read-only"
    cmd = [PATHS.codex_bin, "--no-daemon", "-s", sandbox, "-a", "never", "-C", str(call.cwd),
           "-m", _model_for(call, "codex"), "exec"]
    if session := _session_for(call, "codex"):
        cmd += ["resume", "--json", session, "-"]
    else:
        cmd += ["--json", "-"]
    out, err, rc, secs = _run_process(cmd, call, "codex", stdin_text=call.prompt)
    return _Attempt("codex", _parse_codex(out, err, rc), rc, secs, cmd)


def _run_antigravity(call: AgentCall) -> _Attempt:
    mode = "accept-edits" if _editable(call) else "plan"
    actual_cmd = [PATHS.antigravity_bin, "--output-format", "json", "--model", _model_for(call, "antigravity"),
                  "--mode", mode, "--print-timeout", f"{max(1, call.timeout_s)}s"]
    for directory in call.add_dirs:
        actual_cmd += ["--add-dir", str(directory)]
    if session := _session_for(call, "antigravity"):
        actual_cmd += ["--conversation", session]
    actual_cmd += [f"-p={call.prompt}"]
    out, err, rc, secs = _run_process(actual_cmd, call, "antigravity", stdin_text=None)
    data = _last_json_object(out)
    status = str(data.get("status", "")).upper()
    result = str(data.get("response") or data.get("result") or "")
    usage = data.get("usage", {}) if isinstance(data.get("usage"), dict) else {}
    raw = {"type": "result", "subtype": "success" if status == "SUCCESS" and rc == 0 else "error",
           "is_error": rc != 0 or status != "SUCCESS" or not result.strip(), "result": result,
           "session_id": data.get("conversation_id"), "num_turns": int(data.get("num_turns", 0) or 0),
           "total_cost_usd": 0, "usage": {"input_tokens": int(usage.get("input_tokens", 0) or 0),
                                             "output_tokens": int(usage.get("output_tokens", 0) or 0),
                                             "cache_read_input_tokens": int(usage.get("cache_read_tokens", 0) or 0)},
           "api_error": str(data.get("error") or ""), "stderr_tail": (err or "")[-2000:], "stdout_tail": out[-2000:]}
    display_cmd = actual_cmd[:-1] + ["<prompt supplied via -p>"]
    return _Attempt("antigravity", raw, rc, secs, display_cmd)


def _unavailable(attempt: _Attempt) -> bool:
    raw = attempt.raw
    if attempt.returncode in (126, 127, -9):
        return True
    if raw.get("api_error_status") in (401, 403, 408, 409, 425, 429, 500, 502, 503, 504):
        return True
    text = " ".join(str(raw.get(key) or "") for key in
                    ("api_error", "result", "stderr", "stderr_tail", "stdout_tail")).lower()
    markers = ("usage_limit", "usage limit", "rate_limit", "rate limit", "quota", "resource exhausted",
               "overloaded", "service unavailable", "temporarily unavailable", "authentication", "authenticate",
               "oauth session expired", "not logged in",
               "connection error", "network error", "timed out", "timeout", "no such file", "failed to start",
               "could not resolve", "name resolution", "econnreset", "econnrefused")
    return bool(raw.get("is_error")) and any(marker in text for marker in markers)


def _write_attempt(log_dir: Path, tag: str, call: AgentCall, attempt: _Attempt) -> None:
    prefix = f"{tag}.{attempt.provider}"
    command = " ".join(shlex.quote(part) for part in attempt.command) + f"\n# cwd={call.cwd}\n"
    write_text(log_dir / f"{prefix}.cmd", command)
    write_text(log_dir / f"{prefix}.raw.json", json.dumps(attempt.raw, indent=2))
    write_text(log_dir / f"{prefix}.txt", str(attempt.raw.get("result") or ""))


def run_agent(call: AgentCall, *, log_dir: Path, tag: str) -> AgentResult:
    """Run an agent with audited availability fallback and normalized result JSON."""
    log_dir.mkdir(parents=True, exist_ok=True)
    write_text(log_dir / f"{tag}.prompt.md", call.prompt)
    runners = {"claude": _run_claude, "codex": _run_codex, "antigravity": _run_antigravity}
    attempts: list[_Attempt] = []
    selected: _Attempt | None = None
    providers = _provider_order(call)
    for index, provider in enumerate(providers):
        log(f"{call.role}: {provider} (model={_model_for(call, provider)}, cwd={call.cwd.name})")
        attempt = runners[provider](call)
        attempts.append(attempt)
        _write_attempt(log_dir, tag, call, attempt)
        ok = attempt.returncode == 0 and not attempt.raw.get("is_error", False)
        log(f"{call.role}: {provider} done in {attempt.seconds:.0f}s, turns={attempt.raw.get('num_turns')}, "
            f"cost=${float(attempt.raw.get('total_cost_usd') or 0):.3f}, ok={ok}")
        if ok:
            selected = attempt
            break
        if index + 1 < len(providers) and _unavailable(attempt):
            log(f"{call.role}: {provider} unavailable; falling back to {providers[index + 1]}")
            continue
        selected = attempt
        break
    if selected is None:
        selected = _Attempt("none", {"is_error": True, "result": "no agent provider configured"}, 127, 0, [])

    raw = dict(selected.raw)
    raw["provider"] = selected.provider
    raw["model"] = _model_for(call, selected.provider) if selected.provider in KNOWN_PROVIDERS else ""
    raw["fallback_attempts"] = [
        {"provider": attempt.provider, "ok": attempt.returncode == 0 and not attempt.raw.get("is_error", False),
         "reason": str(attempt.raw.get("api_error") or attempt.raw.get("result") or attempt.raw.get("stderr_tail") or "")[:300]}
        for attempt in attempts
    ]
    session_id = raw.get("session_id")
    if session_id and ":" not in str(session_id):
        session_id = f"{selected.provider}:{session_id}"
        raw["session_id"] = session_id
    command = " ".join(shlex.quote(part) for part in selected.command)
    write_text(log_dir / f"{tag}.cmd", command + f"\n# provider={selected.provider}\n# cwd={call.cwd}\n")
    write_text(log_dir / f"{tag}.raw.json", json.dumps(raw, indent=2))
    text = str(raw.get("result") or "")
    write_text(log_dir / f"{tag}.txt", text)
    return AgentResult(text=text, raw=raw, returncode=selected.returncode,
                       seconds=sum(attempt.seconds for attempt in attempts),
                       session_id=str(session_id) if session_id else None)


def extract_json_block(text: str) -> dict[str, Any] | None:
    """Agents are asked to end with a ```json block; pull the last one out."""
    import re
    blocks = re.findall(r"```json\s*(\{.*?\})\s*```", text, flags=re.S)
    for block in reversed(blocks):
        try:
            return json.loads(block)
        except json.JSONDecodeError:
            continue
    matches = re.findall(r"(\{(?:[^{}]|\{[^{}]*\})*\})", text, flags=re.S)
    for block in reversed(matches):
        try:
            return json.loads(block)
        except json.JSONDecodeError:
            continue
    return None
