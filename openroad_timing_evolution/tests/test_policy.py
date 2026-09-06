import json
import random
import tempfile
import unittest
from pathlib import Path

from openroad_timing_evolution import kernel
from openroad_timing_evolution.policy import Policy, mutate


class PolicyTests(unittest.TestCase):
    def test_rejects_unbounded_or_executable_inputs(self):
        bad = [
            {"enabled": True, "expression": ["div", "load", 1.0]},
            {"enabled": True, "expression": ["add", "load", float("inf")]},
            {"enabled": True, "expression": ["add", "load", 5.0]},
            {"enabled": True, "expression": True},
            {"enabled": False, "expression": "fanout"},
            {"enabled": True, "expression": {"call": "system"}},
        ]
        for item in bad:
            with self.subTest(item=item):
                with self.assertRaises(ValueError):
                    Policy.from_dict(item)

    def test_canonical_policy_id_is_order_independent(self):
        a = Policy.from_dict({"enabled": True, "expression": ["add", "load", ["mul", 0.25, "fanout"]]})
        b = Policy.from_dict({"expression": ["add", "load", ["mul", 0.25, "fanout"]], "enabled": True})
        self.assertEqual(a.id, b.id)
        self.assertEqual(len(a.id), 16)

    def test_mutation_stays_inside_grammar(self):
        rng = random.Random(7)
        parent = Policy.stock()
        for _ in range(25):
            parent = mutate(parent, rng)
            self.assertTrue(parent.enabled)
            self.assertLessEqual(len(parent.tree_json), 8192)

    def test_generated_header_matches_python_ordering(self):
        policy = Policy.from_dict({"enabled": True, "expression": ["add", "load", ["mul", 0.25, "fanout"]]})
        with tempfile.TemporaryDirectory() as tmp:
            result = kernel.check(policy, Path(tmp), samples=30)
        self.assertTrue(result["differential_pass"])
        self.assertGreaterEqual(result["cases"], 34)


if __name__ == "__main__":
    unittest.main()
