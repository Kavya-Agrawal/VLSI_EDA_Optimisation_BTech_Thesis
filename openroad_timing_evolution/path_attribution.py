"""Timing-Path-Guided Mutation (TPGM): attribute critical paths to policy blocks.

After each evaluation, the STA path extraction (tcl/path_extract.tcl) produces
per-path features.  This module maps those features back to policy program blocks
via BLOCK_META, producing attribution weights that bias mutation toward the blocks
most likely to influence currently-critical timing paths.
"""
from __future__ import annotations

import json
import math
from dataclasses import dataclass, field
from pathlib import Path
from typing import Optional

from .policy import BLOCK_META, PROGRAM_OPS


@dataclass(frozen=True)
class CriticalPath:
    endpoint: str
    slack_ns: float
    arrival_ns: float
    cell_count: int
    max_cap_pf: float
    max_fanout: int
    total_load_pf: float
    pin_count: int

    @property
    def criticality(self) -> float:
        return max(0.0, -self.slack_ns) if self.slack_ns < 0 else 0.001


def load_paths(path: Path) -> list[CriticalPath]:
    if not path.exists():
        return []
    data = json.loads(path.read_text())
    return [CriticalPath(**entry) for entry in data]


# Thresholds for feature classification (calibrated to Nangate45 typical values).
LOAD_THRESHOLD_PF = 0.05
FANOUT_THRESHOLD = 8
LATE_POSITION_THRESHOLD = 0.65
EARLY_POSITION_THRESHOLD = 0.20


def classify_path(path: CriticalPath) -> set[str]:
    """Classify a critical path by its dominant physical features."""
    features = set()
    if path.total_load_pf > LOAD_THRESHOLD_PF or path.max_cap_pf > LOAD_THRESHOLD_PF * 0.5:
        features.add("load")
    if path.max_fanout > FANOUT_THRESHOLD:
        features.add("fanout")
    # Approximate topological position from cell count relative to path depth.
    # Deeper paths (more cells) tend to be late in the design.
    if path.cell_count > 15:
        features.add("position_late")
    if path.cell_count <= 5:
        features.add("position_early")
    # High arrival time suggests late path
    if path.arrival_ns > 0 and path.slack_ns < 0:
        features.add("position_late")
    return features


# Which path features map to which BLOCK_META reads.
FEATURE_TO_READS = {
    "load": {"load"},
    "fanout": {"fanout"},
    "position_late": {"position"},
    "position_early": {"position"},
}


def attribute_paths(paths: list[CriticalPath],
                    program: list[str]) -> dict[int, float]:
    """Build attribution weights mapping block indices to influence scores.

    For each critical path, determine which features dominate it, then weight
    the program blocks whose BLOCK_META reads overlap with those features.
    Weight is proportional to path criticality (magnitude of negative slack).
    """
    if not paths or not program:
        return {}

    weights: dict[int, float] = {i: 0.0 for i in range(len(program))}

    for path in paths:
        features = classify_path(path)
        if not features:
            # Unclassified: small uniform contribution to all blocks
            for i in range(len(program)):
                weights[i] += path.criticality * 0.1
            continue

        relevant_reads = set()
        for feat in features:
            relevant_reads |= FEATURE_TO_READS.get(feat, set())

        for i, op in enumerate(program):
            block_reads = set(BLOCK_META[op]["reads"])
            overlap = block_reads & relevant_reads
            if overlap:
                weights[i] += path.criticality * len(overlap) / len(block_reads)

    # Normalize to probability distribution.
    total = sum(weights.values())
    if total > 0:
        weights = {i: w / total for i, w in weights.items()}
    else:
        n = len(program)
        weights = {i: 1.0 / n for i in range(n)}

    return weights


@dataclass
class PathFeedback:
    """Track path-level changes between baseline and candidate."""
    paths_improved: int = 0
    paths_regressed: int = 0
    paths_unchanged: int = 0
    new_critical_paths: int = 0
    path_set_stability: float = 1.0
    mean_slack_delta_ns: float = 0.0

    def to_dict(self):
        return {
            "paths_improved": self.paths_improved,
            "paths_regressed": self.paths_regressed,
            "paths_unchanged": self.paths_unchanged,
            "new_critical_paths": self.new_critical_paths,
            "path_set_stability": round(self.path_set_stability, 4),
            "mean_slack_delta_ns": round(self.mean_slack_delta_ns, 6),
        }


def compare_paths(base_paths: list[CriticalPath],
                  candidate_paths: list[CriticalPath]) -> PathFeedback:
    """Compare path-level results between baseline and candidate runs."""
    feedback = PathFeedback()

    if not base_paths or not candidate_paths:
        return feedback

    base_by_ep = {p.endpoint: p for p in base_paths}
    cand_by_ep = {p.endpoint: p for p in candidate_paths}

    common = set(base_by_ep) & set(cand_by_ep)
    feedback.new_critical_paths = len(set(cand_by_ep) - set(base_by_ep))

    if common:
        feedback.path_set_stability = len(common) / max(len(base_by_ep), len(cand_by_ep))
    else:
        feedback.path_set_stability = 0.0

    deltas = []
    for ep in common:
        delta = cand_by_ep[ep].slack_ns - base_by_ep[ep].slack_ns
        deltas.append(delta)
        if delta > 0.001:
            feedback.paths_improved += 1
        elif delta < -0.001:
            feedback.paths_regressed += 1
        else:
            feedback.paths_unchanged += 1

    if deltas:
        feedback.mean_slack_delta_ns = sum(deltas) / len(deltas)

    return feedback


def format_attribution(weights: dict[int, float], program: list[str]) -> str:
    """Human-readable attribution summary for logging."""
    if not weights:
        return "no attribution (empty program or no paths)"
    lines = []
    for i in sorted(weights, key=lambda i: -weights[i]):
        if i < len(program):
            pct = weights[i] * 100
            lines.append(f"  [{i}] {program[i]}: {pct:.1f}%")
    return "TPGM attribution:\n" + "\n".join(lines)
