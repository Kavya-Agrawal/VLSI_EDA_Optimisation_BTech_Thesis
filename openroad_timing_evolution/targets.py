"""Unified evolution targets for PV-Evolve framework.

Each target defines the source file to evolve, its SSPE block structure,
BLOCK_META for TPGM attribution, and PVCC layer configuration.
"""
from __future__ import annotations

TARGETS = {
    "resizer": {
        "name": "Resizer Setup Path-Driver Priority",
        "source": "src/rsz/src/policy/SetupLegacyBase.cc",
        "header": "src/rsz/src/policy/EvolvedPathDriverPolicy.h",
        "description": "Priority function for setup timing violation repair ordering",
        "blocks": [
            {"name": "load_pressure", "reads": ["load"], "meta": "base timing pressure from net capacitance"},
            {"name": "fanout_shock", "reads": ["load", "fanout"], "meta": "downstream cone pressure"},
            {"name": "late_path_focus", "reads": ["position", "load"], "meta": "prioritize late topological paths"},
            {"name": "stability_damper", "reads": ["position"], "meta": "reduce oscillation from position"},
        ],
        "best_wns_pct": 4.88,
        "candidates_evaluated": 3500,
        "pvcc_pass_rate": 0.673,
    },
    "cts": {
        "name": "CTS Sink Clustering Learning Policy",
        "source": "src/cts/src/LearningPolicyConfig.h",
        "header": None,
        "description": "Machine-learned parameters for clock tree sink clustering",
        "blocks": [
            {"name": "cluster_diameter", "reads": ["diameter", "cap"], "meta": "maximum cluster spatial extent"},
            {"name": "sink_cap_limit", "reads": ["cap", "fanout"], "meta": "capacitance threshold per cluster"},
            {"name": "buffer_distance", "reads": ["wirelength", "skew"], "meta": "buffer insertion spacing"},
            {"name": "skew_weight", "reads": ["skew", "latency"], "meta": "clock skew vs latency tradeoff"},
        ],
        "best_wns_pct": 3.21,
        "candidates_evaluated": 3500,
        "pvcc_pass_rate": 0.602,
    },
    "optmirror": {
        "name": "DPL OptMirror Candidate Ordering",
        "source": "src/dpl/src/OptMirror.cpp",
        "header": None,
        "description": "Mirror optimization candidate ordering in detailed placement",
        "blocks": [
            {"name": "pin_displacement", "reads": ["displacement", "pin_count"], "meta": "pin-weighted displacement score"},
            {"name": "orientation_cost", "reads": ["orientation", "neighbors"], "meta": "cost of flipping relative to neighbors"},
            {"name": "wirelength_delta", "reads": ["wirelength", "displacement"], "meta": "estimated HPWL change"},
        ],
        "best_wns_pct": 1.74,
        "candidates_evaluated": 850,
        "pvcc_pass_rate": 0.718,
    },
}

DEFAULT_TARGET = "resizer"

def get_target(name: str) -> dict:
    if name not in TARGETS:
        raise ValueError(f"Unknown target: {name}. Available: {list(TARGETS.keys())}")
    return TARGETS[name]
