import unittest

from openroad_evolution.candidate import MirrorPolicy


class MirrorPolicyTest(unittest.TestCase):
    def test_baseline_disables_ordering(self):
        header = MirrorPolicy.baseline().to_header()
        self.assertIn("return false", header)

    def test_source_is_deterministic_and_identified(self):
        policy = MirrorPolicy(1.0, -0.25)
        header = policy.to_header()
        self.assertIn(policy.identifier, header)
        self.assertIn("kDegreeWeight = -0.25", header)
        self.assertIn("std::log1p", header)
        self.assertNotIn("kIdWeight", header)
        self.assertEqual(policy, MirrorPolicy.from_dict(policy.to_dict()))

    def test_rejects_invalid_policy(self):
        with self.assertRaises(ValueError):
            MirrorPolicy(float("inf"), 0.0).validate()
        with self.assertRaises(ValueError):
            MirrorPolicy(0.0, 0.0).validate()
        with self.assertRaises(ValueError):
            MirrorPolicy(5.01, 0.0).validate()
