"""ORFS METRICS2.1 parsing, physical-correctness gates, and QoR scoring."""

from __future__ import annotations

from dataclasses import dataclass
import json
import math
from pathlib import Path
import random
import statistics
from typing import Any


_KEYS = {
    "setup_wns": "finish__timing__setup__ws",
    "setup_tns": "finish__timing__setup__tns",
    "hold_wns": "finish__timing__hold__ws",
    "hold_tns": "finish__timing__hold__tns",
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


@dataclass(frozen=True)
class PromotionDecision:
    """A conservative decision based on paired, repeated full-flow runs."""

    promotable: bool
    median_score: float
    lower_confidence_bound: float
    reasons: list[str]


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
    if values["route_drc"] != 0:
        errors.append("detailed routing reports DRC errors")
    if values["antenna_violations"] != 0:
        errors.append("detailed routing reports antenna-violating nets")
    if values["route_drc"] > base["route_drc"]:
        errors.append(
            "detailed-route DRC errors exceed the stock baseline "
            f"({values['route_drc']} > {base['route_drc']})"
        )
    if values["antenna_violations"] > base["antenna_violations"]:
        errors.append("antenna-violating net count exceeds the stock baseline")
    return errors


def _relative_gain(candidate: float, baseline: float, *, higher_is_better: bool) -> float:
    """Signed, scale-safe, bounded gain; positive values are improvements.

    Clipping makes each term lie in [-1, 1]. The composite score is therefore
    bounded as well, so no near-zero baseline can create an arbitrarily large
    score or dominate the bootstrap decision.
    """
    scale = max(abs(baseline), 1.0)
    delta = candidate - baseline
    return max(-1.0, min(1.0, (delta if higher_is_better else -delta) / scale))


def score_candidate(candidate: FlowMetrics, baseline: FlowMetrics) -> float:
    """Composite QoR used only after correctness gates pass.

    Setup and hold timing together receive 85% of the score. Routed wirelength
    and elapsed time discourage a timing improvement that creates impractical
    routes or an unusable runtime cost.
    """
    return (
        0.30
        * _relative_gain(
            candidate.value("setup_wns"), baseline.value("setup_wns"), higher_is_better=True
        )
        + 0.25
        * _relative_gain(
            candidate.value("setup_tns"), baseline.value("setup_tns"), higher_is_better=True
        )
        + 0.15
        * _relative_gain(
            candidate.value("hold_wns"), baseline.value("hold_wns"), higher_is_better=True
        )
        + 0.15
        * _relative_gain(
            candidate.value("hold_tns"), baseline.value("hold_tns"), higher_is_better=True
        )
        + 0.10
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


def median_metrics(replicas: list[FlowMetrics]) -> FlowMetrics:
    """Aggregate replicated runs by median, which limits outlier influence."""
    if not replicas:
        raise ValueError("at least one replica is required")
    return FlowMetrics(
        {
            _KEYS[name]: statistics.median(item.value(name) for item in replicas)
            for name in _KEYS
        }
    )


def _paired_bootstrap_lower_bound(
    candidate: list[FlowMetrics],
    baseline: list[FlowMetrics],
    *,
    samples: int,
    seed: int,
) -> tuple[float, float]:
    """Return mean score and its paired percentile-bootstrap lower bound."""
    if len(candidate) != len(baseline) or not candidate:
        raise ValueError("candidate and baseline replica counts must match and be non-zero")
    if samples < 100:
        raise ValueError("bootstrap_samples must be at least 100")
    deltas = [score_candidate(item, reference) for item, reference in zip(candidate, baseline)]
    rng = random.Random(seed)
    bootstrapped = [
        statistics.fmean(rng.choice(deltas) for _ in deltas) for _ in range(samples)
    ]
    bootstrapped.sort()
    return statistics.fmean(deltas), bootstrapped[max(0, int(0.05 * samples) - 1)]


def assess_promotion(
    candidate: list[FlowMetrics],
    baseline: list[FlowMetrics],
    *,
    timing_absolute_tolerance: float,
    max_relative_wirelength_regression: float,
    max_relative_runtime_regression: float,
    minimum_lower_bound: float,
    bootstrap_samples: int,
    seed: int,
) -> PromotionDecision:
    """Require repeatable improvement without hidden timing or QoR regressions.

    A scalar score ranks search candidates. Promotion is stricter: medians may
    not regress on any setup/hold timing metric beyond the configured absolute
    tolerance, and wirelength/runtime have explicit relative budgets. A paired
    95% bootstrap lower bound must also exceed the requested minimum gain.
    """
    candidate_median = median_metrics(candidate)
    baseline_median = median_metrics(baseline)
    _mean_score, lower_bound = _paired_bootstrap_lower_bound(
        candidate, baseline, samples=bootstrap_samples, seed=seed
    )
    reasons: list[str] = []
    for name in ("setup_wns", "setup_tns", "hold_wns", "hold_tns"):
        if candidate_median.value(name) < baseline_median.value(name) - timing_absolute_tolerance:
            reasons.append(f"median {name} regresses beyond its allowed tolerance")
    if candidate_median.value("route_wirelength") > baseline_median.value(
        "route_wirelength"
    ) * (1 + max_relative_wirelength_regression):
        reasons.append("median routed wirelength exceeds its regression budget")
    if candidate_median.value("runtime") > baseline_median.value("runtime") * (
        1 + max_relative_runtime_regression
    ):
        reasons.append("median runtime exceeds its regression budget")
    if lower_bound <= minimum_lower_bound:
        reasons.append(
            "paired 95% bootstrap lower confidence bound does not exceed "
            f"the promotion threshold ({lower_bound:.6f} <= {minimum_lower_bound:.6f})"
        )
    paired_scores = [score_candidate(item, reference) for item, reference in zip(candidate, baseline)]
    if any(score <= 0.0 for score in paired_scores):
        reasons.append("at least one paired flow seed has a non-positive composite score")
    return PromotionDecision(
        not reasons,
        score_candidate(candidate_median, baseline_median),
        lower_bound,
        reasons,
    )
