"""Paired, fail-closed scoring of a candidate against a reference (baseline or champion).

score(design) = 0.5 * (WNS_cand - WNS_ref) / period + 0.5 * (TNS_cand - TNS_ref) / (period * endpoints)
    (WNS/TNS are negative numbers; a positive score means the candidate is better)
tier score   = mean over designs that ran on both sides
Guards (any one rejects regardless of score): a design failed to evaluate, non-deterministic results,
hold WNS worse than reference by > tolerance, more DRV violations than allowed, placement illegal,
area growth above tolerance."""
from __future__ import annotations

from dataclasses import dataclass, field
from typing import Any

from ..config import Knobs


@dataclass
class Verdict:
    accepted: bool
    score: float
    reasons: list[str] = field(default_factory=list)
    per_design: dict[str, dict[str, Any]] = field(default_factory=dict)

    def as_dict(self) -> dict[str, Any]:
        return {"accepted": self.accepted, "score": round(self.score, 6), "reasons": self.reasons, "per_design": self.per_design}


def design_score(cand: dict[str, Any], ref: dict[str, Any]) -> dict[str, Any]:
    period = float(cand.get("period_ns") or ref.get("period_ns") or 1.0)
    eps = max(1, int(cand.get("endpoints") or ref.get("endpoints") or 1))
    cw, rw = cand["post"]["wns_setup"]["mean"], ref["post"]["wns_setup"]["mean"]
    ct, rt = cand["post"]["tns_setup"]["mean"], ref["post"]["tns_setup"]["mean"]
    d_wns = (cw - rw) / period
    d_tns = (ct - rt) / (period * eps)
    return {
        "score": 0.5 * d_wns + 0.5 * d_tns,
        "wns_cand": cw, "wns_ref": rw, "tns_cand": ct, "tns_ref": rt,
        "d_wns_ns": cw - rw, "d_tns_ns": ct - rt,
        "d_wns_pct_period": 100.0 * d_wns, "d_tns_pct": (100.0 * (ct - rt) / abs(rt)) if rt else 0.0,
        "hold_cand": cand["post"]["wns_hold"]["mean"], "hold_ref": ref["post"]["wns_hold"]["mean"],
        "drv_cand": cand["post"]["drv"], "drv_ref": ref["post"]["drv"],
        "area_cand": cand["post"]["area_um2"]["mean"], "area_ref": ref["post"]["area_um2"]["mean"],
        "placement_violations": cand["post"]["placement_violations"],
        "deterministic": cand.get("deterministic", True),
    }


def judge(cand_agg: dict[str, dict[str, Any]], ref_agg: dict[str, dict[str, Any]], knobs: Knobs, *,
          require_gain: bool = True) -> Verdict:
    reasons: list[str] = []
    per: dict[str, dict[str, Any]] = {}
    scores: list[float] = []
    for key, ref in ref_agg.items():
        cand = cand_agg.get(key)
        if not cand or not cand.get("ok"):
            reasons.append(f"{key}: candidate evaluation failed ({(cand or {}).get('error', 'missing')})")
            continue
        if not ref.get("ok"):
            continue
        ds = design_score(cand, ref)
        per[key] = ds
        scores.append(ds["score"])
        if not ds["deterministic"]:
            reasons.append(f"{key}: non-deterministic results across replicates")
        if ds["hold_cand"] < min(ds["hold_ref"], 0.0) - knobs.hold_wns_tolerance_ns:
            reasons.append(f"{key}: hold WNS regressed {ds['hold_ref']:+.4f} -> {ds['hold_cand']:+.4f} ns")
        if ds["drv_cand"] > ds["drv_ref"] + knobs.drv_tolerance:
            reasons.append(f"{key}: DRV violations {ds['drv_ref']:.0f} -> {ds['drv_cand']:.0f}")
        if ds["placement_violations"] > 0:
            reasons.append(f"{key}: placement has {ds['placement_violations']:.0f} violations after legalization")
        if ds["area_ref"] > 0 and (ds["area_cand"] - ds["area_ref"]) / ds["area_ref"] * 100.0 > knobs.area_tolerance_pct:
            reasons.append(f"{key}: area grew {100.0*(ds['area_cand']-ds['area_ref'])/ds['area_ref']:.1f}% (> {knobs.area_tolerance_pct}%)")
    if not scores:
        return Verdict(False, 0.0, reasons or ["no design could be compared"], per)
    total = sum(scores) / len(scores)
    if require_gain and total < knobs.min_score_gain:
        reasons.append(f"score {total:+.5f} below required gain {knobs.min_score_gain:+.5f}")
    return Verdict(not reasons, total, reasons, per)


def summarize(v: Verdict) -> str:
    lines = [f"{'ACCEPT' if v.accepted else 'REJECT'}  score={v.score:+.5f}"]
    for key, ds in v.per_design.items():
        lines.append(f"  {key:18s} WNS {ds['wns_ref']:+.4f} -> {ds['wns_cand']:+.4f} ns  "
                     f"TNS {ds['tns_ref']:+.3f} -> {ds['tns_cand']:+.3f} ns  score {ds['score']:+.5f}")
    for r in v.reasons:
        lines.append(f"  ! {r}")
    return "\n".join(lines)
