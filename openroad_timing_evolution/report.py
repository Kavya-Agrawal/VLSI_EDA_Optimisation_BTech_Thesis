"""Human-readable summaries for archived Resizer timing-evolution evidence."""

from __future__ import annotations

import json
from pathlib import Path
from statistics import median

from .policy import Policy


METRICS = (
    ("Setup WNS ns", "setup_wns_ns"),
    ("Setup TNS ns", "setup_tns_ns"),
    ("Hold WNS ns", "hold_wns_ns"),
    ("Hold TNS ns", "hold_tns_ns"),
    ("Wirelength um", "wirelength_um"),
    ("Area um2", "area_um2"),
    ("Runtime seconds", "runtime_s"),
    ("Setup skew ns", "clock_skew_setup_ns"),
)


def _read_jsonl(path: Path) -> list[dict]:
    if not path.exists():
        return []
    return [json.loads(line) for line in path.read_text().splitlines() if line.strip()]


def _history(root: Path) -> list[dict]:
    records = _read_jsonl(root / "work" / "memory" / "archive.jsonl")
    if records:
        return records
    out = []
    for archive in sorted((root / "work" / "runs").glob("*/archive.jsonl")):
        out.extend(_read_jsonl(archive))
    return out


def _median(rows: list[dict], key: str):
    values = [row.get(key) for row in rows if key in row]
    return None if not values else median(float(value) for value in values)


def _policy_summary(data: dict) -> str:
    policy = Policy.from_dict(data)
    if not policy.enabled:
        return "Original OpenROAD resizer order. The generated policy is disabled, so path drivers keep stock load-delay ordering."
    data = policy.data()
    if "program" in data:
        return f"Evolved Resizer code. Generated C++ program steps: `{data['program']}`."
    return f"Evolved Resizer path-driver order. Priority expression: `{data['expression']}`."


def build_report(root: Path) -> str:
    records = _history(root)
    evaluated = [r for r in records if r.get("status") == "evaluated" and r.get("metrics")]
    baseline = next((r for r in reversed(evaluated) if not (r.get("policy") or {}).get("enabled")), None)
    feasible = [r for r in records if r.get("status") == "feasible" and r.get("report")]
    feasible.sort(key=lambda r: r["report"].get("score", float("-inf")), reverse=True)
    best = feasible[0] if feasible else None
    best_eval = None
    if best:
        best_eval = next((r for r in reversed(evaluated) if r.get("policy_id") == best.get("policy_id")), None)
    lines = ["# Resizer Timing Evolution Result", ""]
    if baseline is None:
        lines += ["No valid stock baseline is archived yet.", ""]
    else:
        lines += [
            "## Original code",
            "",
            f"- Policy ID: `{baseline['policy_id']}`",
            f"- Summary: {_policy_summary(baseline['policy'])}",
            "",
        ]
    if best is None or best_eval is None:
        lines += ["## Evolved code", "", "No feasible evolved candidate is archived yet.", ""]
    else:
        lines += [
            "## Evolved code",
            "",
            f"- Policy ID: `{best['policy_id']}`",
            f"- Training score: `{best['report']['score']:.6f}`",
            f"- Worst-repeat gain: `{best['report']['worst_repeat_gain']:.6f}`",
            f"- Summary: {_policy_summary(best['policy'])}",
            "",
        ]
        if baseline is not None:
            lines += ["## Original vs evolved metrics", "", "| Metric | Original | Evolved | Delta |", "| --- | ---: | ---: | ---: |"]
            for label, key in METRICS:
                b = _median(baseline["metrics"], key)
                c = _median(best_eval["metrics"], key)
                if b is None or c is None:
                    continue
                lines.append(f"| {label} | {b:.6g} | {c:.6g} | {c - b:.6g} |")
            lines.append("")
    lines += [
        "## Evidence",
        "",
        f"- Memory archive: `{root / 'work' / 'memory' / 'archive.jsonl'}`",
        f"- Run directories: `{root / 'work' / 'runs'}`",
        "",
    ]
    return "\n".join(lines)
