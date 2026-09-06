"""ORFS METRICS2.1 parsing, physical-correctness gates, and QoR scoring."""

from __future__ import annotations

from dataclasses import dataclass
import json
import math
from pathlib import Path
from typing import Any


_KEYS = {
    "setup_wns": "finish__timing__setup__ws",
    "setup_tns": "finish__timing__setup__tns",
    "route_wirelength": "detailedroute__route__wirelength",
    "route_drc": "detailedroute__route__drc_errors",
    "antenna_violations": "detailedroute__antenna__violating__nets",
    "placement_violations": "detailedplace__design__violations",
    "runtime": "total_elapsed_seconds",
}


@dataclass(frozen=True)
class FlowMetrics:
    raw: dict[str, Any]

    @classmethod
    def load(cls, path: str | Path) -> "FlowMetrics":
        return cls(json.loads(Path(path).read_text()))

    def value(self, name: str) -> float:
        key = _KEYS.get(name, name)
        if key not in self.raw:
            raise KeyError(f"required ORFS metric is missing: {key}")
        value = self.raw[key]
        if isinstance(value, bool):
            raise ValueError(f"metric {key} is boolean, not numeric")
        try:
            parsed = float(value)
        except (TypeError, ValueError) as exc:
            raise ValueError(f"metric {key} is not numeric: {value!r}") from exc
        if not math.isfinite(parsed):
            raise ValueError(f"metric {key} is not finite: {value!r}")
        return parsed

    def required_values(self) -> dict[str, float]:
        return {name: self.value(name) for name in _KEYS}


def verify_correctness(candidate: FlowMetrics, baseline: FlowMetrics) -> list[str]:
    """Return all reasons a result is unsafe; an empty list means admissible.

    This separates validity from optimization. A lower score can still be a
    useful trace, but no candidate with a failed compile/regression/flow or a
    physical violation may enter the evolutionary parent pool.
    """
    errors: list[str] = []
    try:
        values = candidate.required_values()
        base = baseline.required_values()
    except (KeyError, ValueError) as exc:
        return [str(exc)]

    if values["placement_violations"] != 0:
        errors.append("detailed placement reports violations")
    if values["route_drc"] > base["route_drc"]:
        errors.append(
            "detailed-route DRC errors exceed the stock baseline "
            f"({values['route_drc']} > {base['route_drc']})"
        )
    if values["antenna_violations"] > base["antenna_violations"]:
        errors.append("antenna-violating net count exceeds the stock baseline")
    return errors


def _relative_gain(candidate: float, baseline: float, *, higher_is_better: bool) -> float:
    """Signed, scale-safe gain; positive values are improvements."""
    scale = max(abs(baseline), 1.0)
    delta = candidate - baseline
    return (delta if higher_is_better else -delta) / scale


def score_candidate(candidate: FlowMetrics, baseline: FlowMetrics) -> float:
    """Composite QoR used only after correctness gates pass.

    WNS and TNS dominate timing closure (80% combined); routed wirelength and
    end-to-end elapsed time discourage solutions that win timing by producing
    impractical routes or excessive runtime.
    """
    return (
        0.45
        * _relative_gain(
            candidate.value("setup_wns"), baseline.value("setup_wns"), higher_is_better=True
        )
        + 0.35
        * _relative_gain(
            candidate.value("setup_tns"), baseline.value("setup_tns"), higher_is_better=True
        )
        + 0.15
        * _relative_gain(
            candidate.value("route_wirelength"),
            baseline.value("route_wirelength"),
            higher_is_better=False,
        )
        + 0.05
        * _relative_gain(
            candidate.value("runtime"), baseline.value("runtime"), higher_is_better=False
        )
    )
