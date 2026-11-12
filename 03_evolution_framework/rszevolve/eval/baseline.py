"""Baseline = stock OpenROAD on every checkpoint, several replicates, both SDC variants.
Writes 05_baseline_results/<pdk>__<design>/<variant>_r<k>/ and 05_baseline_results/{baseline.json,SUMMARY.md}."""
from __future__ import annotations

from pathlib import Path
from typing import Any

from ..config import PATHS, Knobs, designs_for_tier
from ..util import log, now_iso, read_json, write_json, write_text
from .paths import attribute, render_markdown
from .run_eval import aggregate, run_suite


def baseline_path() -> Path:
    return PATHS.baseline / "baseline.json"


def load_baseline() -> dict[str, Any]:
    return read_json(baseline_path(), {}) or {}


def run_baseline(tier: str, knobs: Knobs, *, replicates: int = 3, variants: tuple[str, ...] = ("stressed", "nominal"),
                 only: list[str] | None = None) -> dict[str, Any]:
    keys = only or designs_for_tier(tier)
    data = load_baseline()
    data.setdefault("variants", {})
    for variant in variants:
        runs = run_suite(PATHS.openroad_stock, keys, variant, PATHS.baseline, knobs, replicates=replicates)
        agg = aggregate(runs)
        for k, a in agg.items():
            if a.get("ok"):
                a["attribution"] = attribute(Path(a["dirs"][0]), a["period_ns"])
        data["variants"].setdefault(variant, {}).update(agg)
    data["binary"] = str(PATHS.openroad_stock)
    data["openroad_commit"] = (PATHS.original / "UPSTREAM_COMMIT.txt").read_text().strip() if (PATHS.original / "UPSTREAM_COMMIT.txt").exists() else None
    data["repair_args"] = knobs.repair_timing_args
    data["updated"] = now_iso()
    write_json(baseline_path(), data)
    write_text(PATHS.baseline / "SUMMARY.md", render_summary(data))
    log(f"baseline written: {baseline_path()}")
    return data


def render_summary(data: dict[str, Any]) -> str:
    out = [f"# Baseline (stock OpenROAD)", "", f"binary: `{data.get('binary')}`  commit: `{data.get('openroad_commit')}`  updated: {data.get('updated')}", "",
           f"repair_timing args: `{data.get('repair_args')}`", ""]
    for variant, agg in data.get("variants", {}).items():
        out += [f"## SDC variant: {variant}", "", "| design | period (ns) | endpoints | WNS pre | WNS post | TNS pre | TNS post | hold WNS | area um2 | buffers | repair ms | deterministic |", "|---|---|---|---|---|---|---|---|---|---|---|---|"]
        for k, a in sorted(agg.items()):
            if not a.get("ok"):
                out.append(f"| {k} | - | - | FAILED: {a.get('error')} | | | | | | | | |"); continue
            p = a["post"]
            rep = a.get("repair_ms") or {}
            out.append(f"| {k} | {a['period_ns']:.4g} | {a['endpoints']} | {a['pre']['wns_setup']:+.4f} | {p['wns_setup']['mean']:+.4f} | {a['pre']['tns_setup']:+.3f} | {p['tns_setup']['mean']:+.3f} | {p['wns_hold']['mean']:+.4f} | {p['area_um2']['mean']:.0f} | {p['buffers']['mean']:.0f} | {rep.get('mean', 0):.0f} | {'yes' if a.get('deterministic') else 'NO'} |")
        out.append("")
        for k, a in sorted(agg.items()):
            if a.get("ok") and a.get("attribution"):
                out.append(render_markdown(f"{k} ({variant}) worst paths after stock repair", a["attribution"], None, limit=8))
    return "\n".join(out) + "\n"
