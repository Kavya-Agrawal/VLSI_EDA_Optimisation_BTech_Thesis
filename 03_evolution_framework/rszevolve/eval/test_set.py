"""Held-out TEST evaluation (like a test split in ML).

The TEST tier is never used by the evolution loop and nothing here is written where agents read
(06_evolved_results/<iter>, 10_agent_knowledge, 11_agent_data). Results go to 12_test_results/.

    make test-baseline   stock OpenROAD on TEST designs (once)
    make test-champion   build the current champion, run it on TEST, compare with stock
"""
from __future__ import annotations

import shutil
from pathlib import Path

from ..config import PATHS, Knobs, designs_for_tier
from ..knowledge.ledger import champion_record
from ..util import log, now_iso, read_json, write_json, write_text
from .build import build_candidate
from .run_eval import aggregate, run_suite
from .score import judge, summarize

TEST_ROOT = PATHS.root / "12_test_results"


def test_baseline(knobs: Knobs, replicates: int = 1) -> dict:
    keys = designs_for_tier("TEST")
    runs = run_suite(PATHS.openroad_stock, keys, knobs.sdc_variant, TEST_ROOT / "baseline", knobs, replicates=replicates)
    agg = aggregate(runs)
    write_json(TEST_ROOT / "baseline.json", {"variant": knobs.sdc_variant, "when": now_iso(), "designs": agg})
    log(f"test baseline: {sum(1 for a in agg.values() if a.get('ok'))}/{len(keys)} designs ok")
    return agg


def test_champion(knobs: Knobs, replicates: int = 1) -> int:
    base = (read_json(TEST_ROOT / "baseline.json", {}) or {}).get("designs") or test_baseline(knobs, replicates)
    champ = champion_record()
    it = int(champ.get("iteration", 0))
    if it == 0:
        log("champion is the original rsz; nothing to test"); return 0
    br = build_candidate(PATHS.champion, knobs, tag=f"test_champion_{it:04d}")
    if not br.ok:
        log("champion build failed:\n" + br.diagnostics()); return 1
    binary = PATHS.build / "bin" / f"openroad_champion_{it:04d}"
    shutil.copy2(PATHS.openroad_evolved, binary)
    out = TEST_ROOT / f"champion_{it:04d}"
    runs = run_suite(binary, list(base), knobs.sdc_variant, out / "runs", knobs, replicates=replicates)
    agg = aggregate(runs)
    v = judge(agg, {k: a for k, a in base.items() if a.get("ok")}, knobs, require_gain=False)
    write_json(out / "verdict_vs_stock.json", v.as_dict() | {"champion_iteration": it, "when": now_iso()})
    lines = [f"# Held-out TEST: champion iteration {it} vs stock OpenROAD", "", f"evaluated {now_iso()}", "", "```", summarize(v), "```", "",
             "| design | WNS stock -> champion (ns) | TNS stock -> champion (ns) | TNS change |", "|---|---|---|---|"]
    for k, x in v.per_design.items():
        pct = 100.0 * (x["tns_cand"] - x["tns_ref"]) / abs(x["tns_ref"]) if x["tns_ref"] else 0.0
        lines.append(f"| {k} | {x['wns_ref']:+.4f} -> {x['wns_cand']:+.4f} | {x['tns_ref']:+.3f} -> {x['tns_cand']:+.3f} | {pct:+.1f}% |")
    write_text(out / "SUMMARY.md", "\n".join(lines) + "\n")
    # running history across batches
    hist = read_json(TEST_ROOT / "history.json", []) or []
    hist.append({"champion_iteration": it, "score": v.score, "per_design": v.per_design, "reasons": v.reasons, "when": now_iso()})
    write_json(TEST_ROOT / "history.json", hist)
    print("\n".join(lines))
    return 0
