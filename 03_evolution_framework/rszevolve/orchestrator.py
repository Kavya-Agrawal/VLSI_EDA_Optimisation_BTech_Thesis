"""The evolution loop: plan -> code -> build (+repair) -> gates -> evaluate -> feedback -> record.

One iteration = one candidate. Everything is written to:
  02_openroad_evolved/candidates/<iter>_<cluster>/   rsz tree, candidate.patch, HYPOTHESIS.md
  06_evolved_results/<iter>_<cluster>/               metrics, paths, verdicts, feedback.md, summary.md
  11_agent_data/<iter>/                              prompts, raw JSON, usage
  02_openroad_evolved/lineage.json, 10_agent_knowledge/*, 11_agent_data/budget.json"""
from __future__ import annotations

import time
from pathlib import Path
from typing import Any

from .agents import coder as coder_mod
from .agents.evaluator_agent import feedback as make_feedback
from .agents.planner import plan
from .budget import Budget
from .config import PATHS, Knobs, designs_for_tier
from .eval.baseline import load_baseline
from .eval.build import build_candidate
from .eval.candidate import evaluate
from .eval.score import Verdict
from .knowledge.ledger import (append_ledger, append_section, champion_record, ensure_knowledge_files, load_lineage,
                               next_iteration_number, promote_champion, record_iteration)
from .util import log, now_iso, read_json, write_json, write_text


class AgentUnavailable(RuntimeError):
    """A required Claude call failed before producing usable work."""


def _require_agent(role: str, raw: dict[str, Any]) -> None:
    if not raw.get("is_error") and not raw.get("api_error"):
        return
    reason = str(raw.get("result") or raw.get("api_error") or raw.get("stderr") or "unknown agent error").strip()
    raise AgentUnavailable(f"{role} unavailable: {reason[:500]}")


def latest_feedback() -> str:
    d = load_lineage()
    for it in reversed(d.get("iterations", [])):
        p = Path(it.get("results_dir", "")) / "feedback.md"
        if p.exists():
            return p.read_text()
    return ""


def _preflight(tier: str, knobs: Knobs) -> list[str]:
    designs = designs_for_tier(tier)
    base = load_baseline().get("variants", {}).get(knobs.sdc_variant, {})
    ready = [d for d in designs if base.get(d, {}).get("ok")]
    if not ready:
        raise SystemExit(f"no baseline for tier {tier} / variant {knobs.sdc_variant}: run `make checkpoints baseline`")
    if not PATHS.openroad_stock.exists():
        raise SystemExit("stock binary missing: make build-openroad")
    if not (PATHS.champion / "src").exists():
        raise SystemExit("champion missing: make snapshot")
    if not (PATHS.context / "clusters.json").exists():
        raise SystemExit("09_agent_context/clusters.json missing: make context")
    missing = [d for d in designs if d not in ready]
    if missing:
        log(f"warning: no baseline for {missing}; they are skipped this run")
    return ready


def run_iteration(iteration: int, tier: str, designs: list[str], knobs: Knobs, budget: Budget, *, replicates: int,
                  forced_cluster: str | None = None) -> dict[str, Any]:
    t0 = time.time()
    log_dir = PATHS.agent_data / f"{iteration:04d}"
    log_dir.mkdir(parents=True, exist_ok=True)
    timeline: list[dict[str, Any]] = []
    def mark(step: str, **kw: Any) -> None:
        timeline.append({"step": step, "t": round(time.time() - t0, 1), "ts": now_iso(), **kw})
        write_json(log_dir / "timeline.json", timeline)

    # 1. plan
    h, raw = plan(iteration, knobs, feedback=latest_feedback(), tier=tier, designs=designs, budget_summary=budget.summary(),
                  log_dir=log_dir, forced_cluster=forced_cluster)
    budget.charge(role="planner", iteration=iteration, result=raw)
    _require_agent("planner", raw)
    mark("planned", cluster=h.cluster, title=h.title)
    tag = f"{iteration:04d}_{h.cluster}"

    # 2. code
    remaining = budget.remaining_usd()
    cr = coder_mod.code(iteration, h, knobs, log_dir=log_dir, budget_cap_usd=(remaining if remaining else None))
    budget.charge(role=f"coder:{h.cluster}", iteration=iteration, result=cr.raw)
    _require_agent(f"coder:{h.cluster}", cr.raw)
    mark("coded", files=cr.files_changed)
    if not cr.patch.strip():
        verdict = Verdict(False, 0.0, ["coder produced no change"])
        entry = _finish(iteration, tag, h, cr, None, verdict, log_dir, t0, "no_change")
        return entry

    # 3. build with repair loop
    build = build_candidate(cr.rsz_dir, knobs, tag=tag)
    attempt = 0
    while not build.ok and attempt < knobs.repair_attempts and not budget.exhausted():
        attempt += 1
        log(f"build failed; asking coder to fix (attempt {attempt}/{knobs.repair_attempts})")
        cr = coder_mod.fix(cr, build.diagnostics(), knobs, log_dir=log_dir, attempt=attempt)
        budget.charge(role="coder:fix", iteration=iteration, result=cr.raw)
        _require_agent("coder:fix", cr.raw)
        build = build_candidate(cr.rsz_dir, knobs, tag=f"{tag}_fix{attempt}")
    mark("built", ok=build.ok, attempts=attempt, seconds=round(build.seconds))
    write_text(cr.rsz_dir.parent / "build_diagnostics.txt", build.diagnostics())

    # 4-5. gates + evaluate (evaluate() handles the build-failed case by reading the existing binary only when ok)
    if not build.ok:
        verdict = Verdict(False, 0.0, ["build failed after repairs: " + (build.errors[0] if build.errors else "see log")])
        out = PATHS.results / tag
        out.mkdir(parents=True, exist_ok=True)
        write_text(out / "summary.md", f"# {tag}\n\nBUILD FAILED\n\n```\n{build.diagnostics()}\n```\n")
        write_json(out / "verdict_vs_champion.json", verdict.as_dict())
        write_text(out / "feedback.md", f"# Feedback for iteration {iteration}\n\nBuild failed after {attempt} repair attempts.\n\n```\n{build.diagnostics()[:6000]}\n```\n\nHypothesis:\n{h.hypothesis}\n")
        return _finish(iteration, tag, h, cr, None, verdict, log_dir, t0, "build_failed")
    ce = evaluate(cr.rsz_dir, knobs, tier=tier, replicates=replicates, tag=tag, skip_build=True, design_keys=designs)
    mark("evaluated", accepted=ce.accepted, score=ce.vs_champion.score)

    # 6. evaluator agent feedback
    fb_md, fb_js = make_feedback(iteration, tag, h.cluster, h.hypothesis, ce, knobs, log_dir=log_dir)
    budget.charge(role="evaluator", iteration=iteration, result=read_json(log_dir / "evaluator.raw.json", {}) or {})
    mark("feedback")

    # 7. record
    if ce.accepted:
        promote_champion(cr.rsz_dir, iteration, ce.out_dir, ce.vs_baseline.score, h.hypothesis)
        log(f"iteration {iteration}: NEW CHAMPION (score vs champion {ce.vs_champion.score:+.5f}, vs baseline {ce.vs_baseline.score:+.5f})")
    if fb_js.get("lesson"):
        append_section("lessons.md", f"iteration {iteration} ({h.cluster})", str(fb_js["lesson"]))
    if fb_js.get("dead_end"):
        append_section("dead_ends.md", f"iteration {iteration} ({h.cluster})", str(fb_js["dead_end"]))
    if h.rule_updates.strip():
        append_section("rulebase.md", f"proposed by planner, iteration {iteration}", h.rule_updates)
    return _finish(iteration, tag, h, cr, ce, ce.vs_champion, log_dir, t0, "accepted" if ce.accepted else "rejected")


def _finish(iteration: int, tag: str, h, cr, ce, verdict: Verdict, log_dir: Path, t0: float, status: str) -> dict[str, Any]:
    champ = champion_record()
    entry = {"iteration": iteration, "tag": tag, "status": status, "cluster": h.cluster, "title": h.title, "hypothesis": h.hypothesis,
             "files_changed": cr.files_changed if cr else [], "accepted": bool(ce and ce.accepted), "score_vs_champion": verdict.score,
             "score_vs_baseline": (ce.vs_baseline.score if ce else None), "reasons": verdict.reasons,
             "per_design": (ce.vs_champion.per_design if ce else {}), "champion_after": champ.get("iteration", 0),
             "candidate_dir": str(cr.rsz_dir.parent) if cr else None, "results_dir": str(PATHS.results / tag),
             "agent_data_dir": str(log_dir), "seconds": round(time.time() - t0), "when": now_iso()}
    record_iteration(entry)
    append_ledger(iteration, h.cluster, h.title or h.hypothesis, status, verdict.score, "; ".join(verdict.reasons)[:120])
    write_json(log_dir / "iteration.json", entry)
    log(f"iteration {iteration} done: {status} score={verdict.score:+.5f} in {entry['seconds']}s")
    return entry


def evolve(*, iterations: int, budget_usd: float, max_tokens: int, tier: str, replicates: int, resume: bool,
           knobs: Knobs, cluster: str | None = None) -> int:
    ensure_knowledge_files()
    designs = _preflight(tier, knobs)
    budget = Budget.load(PATHS.agent_data / "budget.json", budget_usd=budget_usd, max_tokens=max_tokens, reset=not resume and next_iteration_number() == 1)
    start = next_iteration_number()
    log(f"evolve: {iterations} iteration(s) from #{start}, tier {tier} ({', '.join(designs)}), {budget.summary()}")
    done = 0
    agent_unavailable = False
    for i in range(start, start + iterations):
        why = budget.exhausted()
        if why:
            log(f"stopping before iteration {i}: {why}")
            break
        try:
            run_iteration(i, tier, designs, knobs, budget, replicates=replicates, forced_cluster=cluster if done == 0 else None)
        except KeyboardInterrupt:
            raise
        except AgentUnavailable as e:
            log(f"stopping at iteration {i}: {e}")
            log("no candidate was evaluated or recorded; resume after the agent limit/error clears")
            agent_unavailable = True
            break
        except Exception as e:  # keep the loop alive; the failure is recorded
            log(f"iteration {i} crashed: {type(e).__name__}: {e}")
            record_iteration({"iteration": i, "status": "crashed", "error": f"{type(e).__name__}: {e}", "when": now_iso()})
        done += 1
        log(f"budget: {budget.summary()}")
    from .report.summary import print_status
    print_status()
    return 2 if agent_unavailable else 0
