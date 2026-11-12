"""Critical-path attribution: turn paths_post.json (from path_report.tcl) into something a planner can
reason about, and diff candidate paths against the reference (baseline or champion).

Each path gets a coarse *cause* label from its structure:
  deep_logic      many stages, modest slew/fanout -> restructuring / sizing along the chain
  high_fanout     a net on the path drives many loads -> cloning / split-load / buffering
  slow_slew       worst slew on the path is large -> weak driver / long wire -> size up / rebuffer
  io_constrained  starts or ends at a port -> input/output delay dominated
  near_zero       slack within 2% of period of zero -> fine-tuning only
These are heuristics for the agents, not ground truth; the raw numbers are passed along too."""
from __future__ import annotations

from pathlib import Path
from typing import Any

from ..util import read_json


def classify(p: dict[str, Any], period_ns: float, *, slew_ref_ns: float | None = None) -> list[str]:
    tags: list[str] = []
    stages = int(p.get("stages", 0))
    fo = int(p.get("max_fanout", 0))
    slew = float(p.get("worst_slew", 0.0))
    slack = float(p.get("slack", 0.0))
    start, end = str(p.get("startpoint", "")), str(p.get("endpoint", ""))
    if stages >= 18:
        tags.append("deep_logic")
    if fo >= 8:
        tags.append("high_fanout")
    slew_ref = slew_ref_ns if slew_ref_ns else 0.06
    if slew >= slew_ref:
        tags.append("slow_slew")
    if "/" not in start or "/" not in end:
        tags.append("io_constrained")
    if period_ns and abs(slack) < 0.02 * period_ns:
        tags.append("near_zero")
    if not tags:
        tags.append("balanced")
    return tags


def worst_cells(p: dict[str, Any], n: int = 4) -> list[dict[str, Any]]:
    """Output pins on the path with the largest slew (proxy for where delay is lost)."""
    outs = [x for x in p.get("pins", []) if x.get("dir") == "output"]
    outs.sort(key=lambda x: -float(x.get("slew", 0.0)))
    return [{"pin": x["pin"], "cell": x.get("cell", ""), "slew": x.get("slew"), "fanout": x.get("fanout")} for x in outs[:n]]


def load_paths(run_dir: Path, which: str = "post") -> list[dict[str, Any]]:
    return read_json(Path(run_dir) / f"paths_{which}.json", []) or []


def attribute(run_dir: Path, period_ns: float) -> dict[str, Any]:
    pre, post = load_paths(run_dir, "pre"), load_paths(run_dir, "post")
    pre_by = {p["endpoint"]: p for p in pre}
    summary: list[dict[str, Any]] = []
    for p in post:
        ep = p["endpoint"]
        before = pre_by.get(ep)
        summary.append({
            "endpoint": ep, "startpoint": p.get("startpoint"),
            "slack": p.get("slack"), "slack_before_repair": before.get("slack") if before else None,
            "stages": p.get("stages"), "max_fanout": p.get("max_fanout"), "worst_slew": p.get("worst_slew"),
            "tags": classify(p, period_ns), "worst_cells": worst_cells(p),
            "cells_on_path": [x.get("cell") for x in p.get("pins", []) if x.get("dir") == "output"],
        })
    tag_hist: dict[str, int] = {}
    for s in summary:
        for t in s["tags"]:
            tag_hist[t] = tag_hist.get(t, 0) + 1
    fixed = [ep for ep in pre_by if ep not in {p["endpoint"] for p in post} ]
    return {"paths": summary, "tag_histogram": tag_hist, "endpoints_no_longer_in_worst_list": fixed[:20]}


def diff_against(cand_dir: Path, ref_dir: Path) -> dict[str, Any]:
    """Which worst endpoints are new, gone, better or worse compared with the reference run."""
    c = {p["endpoint"]: float(p["slack"]) for p in load_paths(cand_dir)}
    r = {p["endpoint"]: float(p["slack"]) for p in load_paths(ref_dir)}
    better = sorted([(ep, r[ep], c[ep]) for ep in c if ep in r and c[ep] > r[ep] + 1e-6], key=lambda x: x[1])
    worse = sorted([(ep, r[ep], c[ep]) for ep in c if ep in r and c[ep] < r[ep] - 1e-6], key=lambda x: x[2])
    return {
        "new_in_worst_list": [ep for ep in c if ep not in r][:15],
        "gone_from_worst_list": [ep for ep in r if ep not in c][:15],
        "improved": [{"endpoint": e, "ref": a, "cand": b} for e, a, b in better[:15]],
        "regressed": [{"endpoint": e, "ref": a, "cand": b} for e, a, b in worse[:15]],
    }


def render_markdown(design: str, attr: dict[str, Any], diff: dict[str, Any] | None, limit: int = 10) -> str:
    lines = [f"### {design}", "", "| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |", "|---|---|---|---|---|---|---|---|---|"]
    for i, p in enumerate(attr["paths"][:limit], 1):
        wc = ", ".join(f"{x['cell']}@{x['pin']} (slew {x['slew']})" for x in p["worst_cells"][:2])
        lines.append(f"| {i} | `{p['endpoint']}` | {p['slack']} | {p['slack_before_repair']} | {p['stages']} | {p['max_fanout']} | {p['worst_slew']} | {' '.join(p['tags'])} | {wc} |")
    lines.append("")
    lines.append("Tag histogram: " + ", ".join(f"{k}={v}" for k, v in sorted(attr["tag_histogram"].items(), key=lambda kv: -kv[1])))
    if diff:
        lines.append("")
        lines.append(f"vs reference: improved {len(diff['improved'])}, regressed {len(diff['regressed'])}, new in worst list {len(diff['new_in_worst_list'])}, gone {len(diff['gone_from_worst_list'])}")
        for d in diff["regressed"][:5]:
            lines.append(f"- regressed `{d['endpoint']}`: {d['ref']:+.4f} -> {d['cand']:+.4f}")
        for d in diff["improved"][:5]:
            lines.append(f"- improved `{d['endpoint']}`: {d['ref']:+.4f} -> {d['cand']:+.4f}")
    return "\n".join(lines) + "\n"
