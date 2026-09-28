import unittest

from openroad_timing_evolution.policy import Policy
from openroad_timing_evolution.search import evolve


def row(policy_id, replica, setup_wns=-0.10, setup_tns=-1.00):
    return {
        "design": "gcd",
        "replica": replica,
        "policy_id": policy_id,
        "binary_sha256": "a" * 64,
        "audit_binary_sha256": "b" * 64,
        "protocol_sha256": "c" * 64,
        "formal_pass": True,
        "audit_pass": True,
        "flow_complete": True,
        "constraints_pass": True,
        "setup_wns_ns": setup_wns,
        "setup_tns_ns": setup_tns,
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
    }


class FakeCampaign:
    def __init__(self, history=None):
        self.config = {
            "seed": 41,
            "train": ["gcd"],
            "validation": ["gcd"],
            "test": ["gcd"],
            "replicates": 3,
            "max_area_regression": 0.02,
            "max_wirelength_regression": 0.02,
            "max_runtime_regression": 0.20,
            "min_improvement": 0.0001,
        }
        self.protocol_sha = "p" * 64
        self.records = list(history or [])

    def history(self):
        return self.records

    def archive(self, record):
        self.records.append({**record, "protocol_sha256": self.protocol_sha})

    def write(self, _name, _data):
        pass

    def baseline(self, designs):
        policy_id = Policy.stock().id
        return [row(policy_id, replica) for replica in range(self.config["replicates"])]

    def evaluate(self, policy, designs):
        return [row(policy.id, replica, setup_wns=-0.05, setup_tns=-0.8) for replica in range(self.config["replicates"])]


class SearchResumeTests(unittest.TestCase):
    def test_second_run_skips_previously_proposed_policy(self):
        first = FakeCampaign()
        evolve(first, generations=1, population=1)
        first_policy = next(r["policy_id"] for r in first.records if r.get("status") == "proposed")
        second = FakeCampaign(first.records)
        evolve(second, generations=1, population=1)
        proposed = [r["policy_id"] for r in second.records if r.get("status") == "proposed"]
        self.assertEqual(len(proposed), 2)
        self.assertNotEqual(first_policy, proposed[-1])


if __name__ == "__main__":
    unittest.main()
