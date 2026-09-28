"""Human-readable summaries for archived OptMirror evolution evidence."""

from __future__ import annotations

import json
from pathlib import Path
from statistics import median

from .candidate import MirrorPolicy, describe_program


METRICS = (
    ("Setup WNS", "finish__timing__setup__ws"),
    ("Setup TNS", "finish__timing__setup__tns"),
    ("Hold WNS", "finish__timing__hold__ws"),
    ("Hold TNS", "finish__timing__hold__tns"),
    ("Route wirelength", "detailedroute__route__wirelength"),
    ("Runtime seconds", "total_elapsed_seconds"),
)


def _records(archive: Path) -> list[dict]:
    if not archive.exists():
        return []
    return [json.loads(line) for line in archive.read_text().splitlines() if line.strip()]


def _aggregate(record: dict, key: str):
    values = [replica.get(key) for replica in record.get("replicas") or [] if key in replica]
    if values:
        return median(float(value) for value in values)
    metrics = record.get("metrics") or {}
    value = metrics.get(key)
    return None if value is None else float(value)


def _policy_summary(policy: dict) -> str:
    p = MirrorPolicy.from_dict(policy)
    if not p.enabled:
        return "Original OpenROAD order. The generated policy is disabled, so OptMirror processes candidates in stock order."
    return (
        "Evolved OptMirror code using Segmented Semantic Program Evolution. "
        f"{describe_program(p.program)} with legacy weights "
        f"hpwl={p.hpwl_weight:.4g}, degree={p.degree_weight:.4g}."
    )


def build_report(archive: Path) -> str:
    records = _records(archive)
    baseline = next((r for r in reversed(records) if not r["policy"].get("enabled") and r.get("valid")), None)
    candidates = [
        r for r in records
        if r["policy"].get("enabled") and r.get("valid") and r.get("score") is not None
    ]
    candidates.sort(key=lambda r: r["score"], reverse=True)
    lines = ["# OptMirror Evolution Result", ""]
    if baseline is None:
        lines += ["No valid stock baseline is archived yet.", ""]
    else:
        lines += [
            "## Original code",
            "",
            f"- Candidate ID: `{baseline['identifier']}`",
            f"- Summary: {_policy_summary(baseline['policy'])}",
            "",
        ]
    if not candidates:
        lines += ["## Evolved code", "", "No valid evolved candidate is archived yet.", ""]
    else:
        best = candidates[0]
        lines += [
            "## Evolved code",
            "",
            f"- Candidate ID: `{best['identifier']}`",
            f"- Score: `{best['score']:.6f}`",
            f"- Summary: {_policy_summary(best['policy'])}",
            f"- Promotable on training: `{bool((best.get('promotion') or {}).get('promotable'))}`",
            "",
        ]
        if baseline is not None:
            lines += ["## Original vs evolved metrics", "", "| Metric | Original | Evolved | Delta |", "| --- | ---: | ---: | ---: |"]
            for label, key in METRICS:
                b = _aggregate(baseline, key)
                c = _aggregate(best, key)
                if b is None or c is None:
                    continue
                lines.append(f"| {label} | {b:.6g} | {c:.6g} | {c - b:.6g} |")
            lines.append("")
    lines += [
        "## Evidence",
        "",
        f"- Archive: `{archive}`",
        "- Generated run directories are under `openroad_evolution/.evolution/runs/`.",
        "",
    ]
    return "\n".join(lines)
