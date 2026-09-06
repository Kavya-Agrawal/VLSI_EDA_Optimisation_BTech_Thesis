"""Fail-closed evidence contract and paired, design-balanced timing scoring."""
from __future__ import annotations

import math
import statistics
import re

class Rejected(ValueError):
    pass


TIMING = ("setup_wns_ns", "setup_tns_ns", "hold_wns_ns", "hold_tns_ns")
ZERO = ("placement_violations", "route_drc", "antenna_nets", "antenna_pins",
        "max_slew_violations", "max_cap_violations", "max_fanout_violations")
POSITIVE = ("area_um2", "wirelength_um", "runtime_s", "clock_period_ns", "endpoint_count")
EVIDENCE = ("formal_pass", "audit_pass", "flow_complete", "constraints_pass")


def validate(m):
    for name in (*TIMING, *ZERO, *POSITIVE):
        v = m.get(name)
        if type(v) not in (int, float) or not math.isfinite(v):
            raise Rejected(f"missing/non-finite/non-numeric metric: {name}")
    for name in ZERO:
        if m[name] != 0 or type(m[name]) is not int:
            raise Rejected(f"physical/electrical gate failed: {name}")
    for name in POSITIVE:
        if m[name] <= 0:
            raise Rejected(f"metric must be positive: {name}")
    if type(m["endpoint_count"]) is not int:
        raise Rejected("endpoint_count must be integer")
    for name in TIMING:
        if m[name] > 0:
            raise Rejected(f"negative-slack metric has positive value: {name}")
    if m["setup_tns_ns"] > m["setup_wns_ns"]:
        raise Rejected("setup TNS cannot be better than setup WNS")
    if m["hold_tns_ns"] > m["hold_wns_ns"]:
        raise Rejected("hold TNS cannot be better than hold WNS")
    for name in EVIDENCE:
        if m.get(name) is not True:
            raise Rejected(f"missing successful evidence: {name}")
    for name in ("binary_sha256", "audit_binary_sha256", "protocol_sha256"):
        if type(m.get(name)) is not str or not re.fullmatch(r"[0-9a-f]{64}", m[name]):
            raise Rejected(f"missing provenance: {name}")
    if type(m.get("policy_id")) is not str or not re.fullmatch(r"[0-9a-f]{16}", m["policy_id"]):
        raise Rejected("missing provenance: policy_id")
    if type(m.get("design")) is not str or not re.fullmatch(r"[a-z0-9_]+", m["design"]):
        raise Rejected("missing provenance: design")
    if type(m.get("replica")) is not int or m["replica"] < 0:
        raise Rejected("missing provenance: replica")
    for name in ("clock_skew_setup_ns", "clock_skew_hold_ns"):
        if name in m and (type(m[name]) not in (int, float) or not math.isfinite(m[name])):
            raise Rejected(f"missing/non-finite/non-numeric metric: {name}")
    return m


def compare(base, candidate, config):
    validate(base)
    validate(candidate)
    for k in ("design", "replica", "protocol_sha256", "audit_binary_sha256", "clock_period_ns", "endpoint_count"):
        if base[k] != candidate[k]:
            raise Rejected(f"unpaired or incompatible measurement: {k}")
    for k in TIMING:
        if candidate[k] < base[k]:
            raise Rejected(f"timing regression: {k}")
    for k, cap in (("area_um2", "max_area_regression"),
                   ("wirelength_um", "max_wirelength_regression"),
                   ("runtime_s", "max_runtime_regression")):
        if candidate[k] > base[k] * (1 + config[cap]):
            raise Rejected(f"resource regression: {k}")
    # Normalize WNS by period; TNS by period * constrained endpoint count.
    # Units and design size cannot silently change the objective.
    period = base["clock_period_ns"]
    return (0.5 * (candidate["setup_wns_ns"] - base["setup_wns_ns"]) / period
            + 0.5 * (candidate["setup_tns_ns"] - base["setup_tns_ns"])
            / (period * base["endpoint_count"]))


def assess(baselines, candidates, designs, config, require_improvement=True):
    expected = {(d, r) for d in designs for r in range(config["replicates"])}
    def keyed(rows):
        result = {}
        for row in rows:
            key = (row["design"], row["replica"])
            if key in result:
                raise Rejected("duplicate design/replica record")
            result[key] = row
        if set(result) != expected:
            raise Rejected("incomplete or unexpected benchmark matrix")
        return result
    b, c = keyed(baselines), keyed(candidates)
    if len({row["policy_id"] for row in candidates}) != 1:
        raise Rejected("mixed candidate identities")
    gains = {key: compare(b[key], c[key], config) for key in sorted(expected)}
    per_design = {d: statistics.median(gains[d,r] for r in range(config["replicates"])) for d in designs}
    score = statistics.mean(per_design.values())
    # Require repeatable gain: average each design's worst observed replicate.
    # This is a conservative observed bound, NOT a statistical confidence interval.
    lower = statistics.mean(min(gains[d,r] for r in range(config["replicates"])) for d in designs)
    if require_improvement and lower <= config["min_improvement"]:
        raise Rejected("no repeatable setup timing improvement")
    return {"score": score, "worst_repeat_gain": lower, "per_design": per_design}
