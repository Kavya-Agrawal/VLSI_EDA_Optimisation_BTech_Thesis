import copy
import unittest

from openroad_timing_evolution.metrics import Rejected, assess, compare, validate


CFG = {
    "replicates": 3,
    "max_area_regression": 0.02,
    "max_wirelength_regression": 0.02,
    "max_runtime_regression": 0.20,
    "min_improvement": 0.0001,
}


def row(design="gcd", replica=0, policy_id="1234567890abcdef", wns=-0.10, tns=-1.00):
    return {
        "design": design,
        "replica": replica,
        "policy_id": policy_id,
        "binary_sha256": "a" * 64,
        "audit_binary_sha256": "b" * 64,
        "protocol_sha256": "c" * 64,
        "formal_pass": True,
        "audit_pass": True,
        "flow_complete": True,
        "constraints_pass": True,
        "setup_wns_ns": wns,
        "setup_tns_ns": tns,
        "hold_wns_ns": 0.0,
        "hold_tns_ns": 0.0,
        "placement_violations": 0,
        "route_drc": 0,
        "antenna_nets": 0,
        "antenna_pins": 0,
        "max_slew_violations": 0,
        "max_cap_violations": 0,
        "max_fanout_violations": 0,
        "area_um2": 100.0,
        "wirelength_um": 200.0,
        "runtime_s": 30.0,
        "clock_period_ns": 10.0,
        "endpoint_count": 100,
        "clock_skew_setup_ns": 0.02,
        "clock_skew_hold_ns": 0.01,
    }


class MetricsTests(unittest.TestCase):
    def test_validate_rejects_missing_evidence(self):
        m = row()
        m["formal_pass"] = False
        with self.assertRaises(Rejected):
            validate(m)

    def test_validate_rejects_positive_slack_and_bad_tns_relationship(self):
        with self.assertRaises(Rejected):
            validate(row(wns=0.01))
        with self.assertRaises(Rejected):
            validate(row(wns=-1.0, tns=-0.5))

    def test_compare_rejects_timing_regression(self):
        base = row()
        candidate = copy.deepcopy(base)
        candidate["setup_wns_ns"] = -0.20
        with self.assertRaises(Rejected):
            compare(base, candidate, CFG)

    def test_compare_rejects_unpaired_runs(self):
        base = row()
        candidate = copy.deepcopy(base)
        candidate["replica"] = 2
        with self.assertRaises(Rejected):
            compare(base, candidate, CFG)

    def test_assess_requires_complete_design_replicate_matrix(self):
        baseline = [row(replica=i) for i in range(3)]
        candidate = [row(replica=i, policy_id="fedcba0987654321", wns=-0.05, tns=-0.8) for i in range(2)]
        with self.assertRaises(Rejected):
            assess(baseline, candidate, ["gcd"], CFG, require_improvement=False)

    def test_assess_accepts_repeatable_improvement(self):
        baseline = [row(replica=i) for i in range(3)]
        candidate = [row(replica=i, policy_id="fedcba0987654321", wns=-0.05, tns=-0.8) for i in range(3)]
        report = assess(baseline, candidate, ["gcd"], CFG)
        self.assertGreater(report["worst_repeat_gain"], 0)


if __name__ == "__main__":
    unittest.main()
