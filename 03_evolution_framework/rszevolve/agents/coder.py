"""Coding sub-agent dispatcher: one cluster-scoped Claude session that edits a candidate rsz tree.

The candidate tree is a copy of the champion under 02_openroad_evolved/candidates/<iter>_<id>/rsz. The agent's cwd
is that tree; its context pack (dossier, cards, eval contract) is inlined into the prompt and also reachable via
--add-dir. Compile errors come back through `fix()` which resumes the same session."""
from __future__ import annotations

import shutil
import subprocess
from dataclasses import dataclass
from pathlib import Path
from typing import Any

from ..config import PATHS, Knobs
from ..util import log, read_json, write_text
from .claude_runner import EDIT_TOOLS, AgentCall, extract_json_block, run_agent
from .planner import Hypothesis


@dataclass
class CodeResult:
    rsz_dir: Path
    session_id: str | None
    files_changed: list[str]
    summary: str
    patch: str
    raw: dict[str, Any]


def new_candidate_dir(iteration: int, cluster: str) -> Path:
    cand = PATHS.candidates / f"{iteration:04d}_{cluster}"
    if cand.exists():
        shutil.rmtree(cand)
    cand.mkdir(parents=True)
    # OpenROAD's rsz tests contain relative symlinks whose targets live outside
    # this isolated snapshot. Preserve the links instead of dereferencing them.
    shutil.copytree(PATHS.champion, cand / "rsz", symlinks=True)
    return cand


def _cluster_pack(cluster: str) -> tuple[dict[str, Any], str, str, str]:
    clusters = (read_json(PATHS.context / "clusters.json", {}) or {}).get("clusters", {})
    c = clusters.get(cluster, {"editable": [], "readonly_context": []})
    dossier_p = PATHS.context / "algorithms" / f"{cluster}.md"
    dossier = dossier_p.read_text() if dossier_p.exists() else "(dossier not generated yet; read the sources and 00_BIG_PICTURE.md)"
    contract_p = PATHS.context / "EVAL_CONTRACT.md"
    contract = contract_p.read_text() if contract_p.exists() else ""
    return c, dossier, contract, "\n".join(f"- src/{e}" for e in c.get("editable", []))


def make_patch(cand_rsz: Path) -> str:
    # BSD diff reports dangling symlinks as "unknown type" on stdout, which
    # looks like a non-empty patch. Git's no-index diff compares link objects
    # correctly and uses the usual 0=same, 1=different return codes.
    res = subprocess.run(["git", "diff", "--no-index", "--", str(PATHS.champion), str(cand_rsz)],
                         capture_output=True, text=True)
    if res.returncode not in (0, 1):
        raise RuntimeError(f"candidate diff failed: {(res.stderr or res.stdout)[-1000:]}")
    return res.stdout


def code(iteration: int, h: Hypothesis, knobs: Knobs, *, log_dir: Path, budget_cap_usd: float | None = None) -> CodeResult:
    cand = new_candidate_dir(iteration, h.cluster)
    rsz = cand / "rsz"
    c, dossier, contract, editable = _cluster_pack(h.cluster)
    prompt = (PATHS.prompts / "coder.md").read_text()
    for k, v in {"CLUSTER": h.cluster, "HYPOTHESIS": f"**{h.title}**\n\n{h.hypothesis}\n\nSuggested files: {', '.join(h.files)}\nSuccess criteria: {h.success_criteria}\nRisk: {h.risk}",
                 "DOSSIER": dossier[:60000], "EDITABLE": editable, "READONLY": ", ".join(c.get("readonly_context", [])), "EVAL_CONTRACT": contract}.items():
        prompt = prompt.replace("{{" + k + "}}", v)
    call = AgentCall(role=f"coder:{h.cluster}", prompt=prompt, cwd=rsz, model=knobs.coder_model, max_turns=knobs.coder_max_turns,
                     allowed_tools=list(EDIT_TOOLS), add_dirs=[PATHS.context, PATHS.original], max_budget_usd=budget_cap_usd,
                     bash_allow=["Bash(grep *)", "Bash(rg *)", "Bash(ls *)", "Bash(cat *)", "Bash(head *)", "Bash(wc *)", "Bash(diff *)"])
    res = run_agent(call, log_dir=log_dir, tag="coder")
    js = extract_json_block(res.text) or {}
    patch = make_patch(rsz)
    write_text(cand / "candidate.patch", patch)
    if not (rsz / "HYPOTHESIS.md").exists():
        write_text(rsz / "HYPOTHESIS.md", f"# {h.title}\n\n{h.hypothesis}\n\n(agent did not write HYPOTHESIS.md; planner text used)\n")
    shutil.copy2(rsz / "HYPOTHESIS.md", cand / "HYPOTHESIS.md")
    changed = [str(f) for f in js.get("files_changed", [])] or sorted({l.split()[1] for l in patch.splitlines() if l.startswith("+++ ") and "/dev/null" not in l})
    log(f"coder: {len(changed)} files changed, patch {len(patch.splitlines())} lines")
    return CodeResult(rsz, res.session_id, changed, str(js.get("summary", "")), patch, res.raw)


def fix(cr: CodeResult, diagnostics: str, knobs: Knobs, *, log_dir: Path, attempt: int) -> CodeResult:
    prompt = (PATHS.prompts / "coder_fix.md").read_text().replace("{{DIAGNOSTICS}}", diagnostics[:20000])
    call = AgentCall(role="coder:fix", prompt=prompt, cwd=cr.rsz_dir, model=knobs.coder_model, max_turns=max(20, knobs.coder_max_turns // 2),
                     allowed_tools=list(EDIT_TOOLS), add_dirs=[PATHS.context, PATHS.original], resume_session=cr.session_id,
                     bash_allow=["Bash(grep *)", "Bash(rg *)", "Bash(ls *)", "Bash(cat *)", "Bash(head *)", "Bash(diff *)"])
    res = run_agent(call, log_dir=log_dir, tag=f"coder_fix{attempt}")
    if not res.ok and cr.session_id:
        # resume can fail if the session was not persisted; retry fresh with the same prompt + hypothesis context
        call.resume_session = None
        call.prompt = "You are fixing a failed build of the candidate rsz tree in your cwd (see HYPOTHESIS.md).\n\n" + prompt
        res = run_agent(call, log_dir=log_dir, tag=f"coder_fix{attempt}_fresh")
    js = extract_json_block(res.text) or {}
    patch = make_patch(cr.rsz_dir)
    write_text(cr.rsz_dir.parent / "candidate.patch", patch)
    return CodeResult(cr.rsz_dir, res.session_id or cr.session_id, [str(f) for f in js.get("files_changed", [])] or cr.files_changed,
                      str(js.get("summary", cr.summary)), patch, res.raw)
