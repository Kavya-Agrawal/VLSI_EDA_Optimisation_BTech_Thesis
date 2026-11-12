"""Evaluate one rsz tree end to end: build -> gates -> benchmark runs -> compare with baseline and champion.

Writes everything under 06_evolved_results/<tag>/:
  build.json, gates/, runs/<design>/<variant>_r<k>/, aggregate.json, verdict_vs_baseline.json,
  verdict_vs_champion.json, paths_attribution.json, summary.md
Returns the Verdict against the champion (the acceptance decision)."""
from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Any

from ..config import PATHS, Knobs, designs_for_tier
from ..util import log, now_iso, read_json, write_json, write_text
from .baseline import load_baseline
from .build import BuildResult, build_candidate
from .gates import GateResult, run_gates
from .paths import attribute, diff_against, render_markdown
from .run_eval import aggregate, run_suite
from .score import Verdict, judge, summarize


@dataclass
class CandidateEval:
    tag: str
    out_dir: Path
    build: BuildResult | None
    gates: GateResult | None
    aggregate: dict[str, Any]
    vs_baseline: Verdict
    vs_champion: Verdict
    attribution: dict[str, Any]

    @property
    def accepted(self) -> bool:
        return self.vs_champion.accepted


def champion_aggregate(variant: str) -> dict[str, Any] | None:
    """The champion's most recent evaluation on this variant (falls back to baseline when champion == original)."""
    rec = read_json(PATHS.evolved / "champion.json", {}) or {}
    agg_path = rec.get("aggregate_path")
    if agg_path and Path(agg_path).exists():
        return read_json(Path(agg_path), {}).get(variant)
    return None


def evaluate_rsz_tree(rsz_dir: Path, knobs: Knobs, *, tier: str = "A", replicates: int = 2, tag: str = "manual",
                      skip_build: bool = False, skip_gates: bool = False, design_keys: list[str] | None = None,
                      results_root: Path | None = None) -> Verdict:
    ce = evaluate(rsz_dir, knobs, tier=tier, replicates=replicates, tag=tag, skip_build=skip_build,
                  skip_gates=skip_gates, design_keys=design_keys, results_root=results_root)
    print(summarize(ce.vs_champion))
    return ce.vs_champion


def evaluate(rsz_dir: Path, knobs: Knobs, *, tier: str = "A", replicates: int = 2, tag: str = "manual",
             skip_build: bool = False, skip_gates: bool = False, design_keys: list[str] | None = None,
             results_root: Path | None = None) -> CandidateEval:
    rsz_dir = Path(rsz_dir).resolve()
    out = (results_root or PATHS.results) / tag
    out.mkdir(parents=True, exist_ok=True)
    variant = knobs.sdc_variant
    keys = design_keys or designs_for_tier(tier)
    base = load_baseline().get("variants", {}).get(variant, {})
    base = {k: v for k, v in base.items() if k in keys and v.get("ok")}
    if not base:
        raise SystemExit(f"no baseline for variant {variant!r} and tier {tier}; run `make baseline`")

    build: BuildResult | None = None
    if not skip_build:
        build = build_candidate(rsz_dir, knobs, tag=tag)
        write_json(out / "build.json", {"ok": build.ok, "seconds": build.seconds, "errors": build.errors, "warnings": build.warnings[:50], "log": str(build.log_path)})
        if not build.ok:
            v = Verdict(False, 0.0, ["build failed: " + (build.errors[0] if build.errors else "see build log")])
            write_json(out / "verdict_vs_champion.json", v.as_dict())
            write_text(out / "summary.md", f"# {tag}\n\nBUILD FAILED\n\n```\n{build.diagnostics()}\n```\n")
            return CandidateEval(tag, out, build, None, {}, v, v, {})
    binary = PATHS.openroad_evolved
    if not binary.exists():
        raise SystemExit(f"{binary} missing; build first")

    gates: GateResult | None = None
    if not skip_gates:
        gates = run_gates(rsz_dir, binary, knobs, out / "gates")
        if not gates.passed:
            v = Verdict(False, 0.0, ["gates failed: " + "; ".join([f"{k}={s}" for k, s in {**gates.unit_tests, **gates.smoke_tests}.items() if s not in ("ok", "PASSED", "missing", "MISSING")][:5])])
            write_json(out / "verdict_vs_champion.json", v.as_dict())
            write_text(out / "summary.md", f"# {tag}\n\nGATES FAILED\n\n```\n{gates.report()}\n```\n")
            return CandidateEval(tag, out, build, gates, {}, v, v, {})

    runs = run_suite(binary, keys, variant, out / "runs", knobs, replicates=replicates)
    agg = aggregate(runs)
    write_json(out / "aggregate.json", {variant: agg, "tier": tier, "replicates": replicates, "when": now_iso(), "rsz_dir": str(rsz_dir)})

    vs_base = judge(agg, base, knobs, require_gain=False)
    champ = champion_aggregate(variant) or base
    vs_champ = judge(agg, champ, knobs, require_gain=True)
    write_json(out / "verdict_vs_baseline.json", vs_base.as_dict())
    write_json(out / "verdict_vs_champion.json", vs_champ.as_dict())

    attribution: dict[str, Any] = {}
    md = [f"# Candidate `{tag}`", "", f"tier {tier}, variant `{variant}`, replicates {replicates}, evaluated {now_iso()}", "",
          "## Verdict vs champion", "", "```", summarize(vs_champ), "```", "", "## Verdict vs baseline (stock OpenROAD)", "", "```", summarize(vs_base), "```", "",
          "## Worst paths after repair (candidate)", ""]
    for key, a in agg.items():
        if not a.get("ok"):
            md.append(f"### {key}\n\nFAILED: {a.get('error')}\n"); continue
        attr = attribute(Path(a["dirs"][0]), a["period_ns"])
        ref_dirs = (base.get(key) or {}).get("dirs") or []
        diff = diff_against(Path(a["dirs"][0]), Path(ref_dirs[0])) if ref_dirs else None
        attribution[key] = {"attribution": attr, "diff_vs_baseline": diff}
        md.append(render_markdown(key, attr, diff))
    write_json(out / "paths_attribution.json", attribution)
    if gates:
        md += ["## Gates", "", "```", gates.report(), "```", ""]
    if build:
        md += ["## Build", "", f"{build.seconds:.0f} s, {len(build.warnings)} warnings", ""]
    write_text(out / "summary.md", "\n".join(md))
    log(f"candidate {tag}: {'ACCEPT' if vs_champ.accepted else 'REJECT'} score={vs_champ.score:+.5f} (vs baseline {vs_base.score:+.5f})")
    return CandidateEval(tag, out, build, gates, agg, vs_base, vs_champ, attribution)
