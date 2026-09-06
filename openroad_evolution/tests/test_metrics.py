import unittest

from openroad_evolution.metrics import FlowMetrics, score_candidate, verify_correctness


def metrics(**overrides):
    values = {
        "finish__timing__setup__ws": -0.20,
        "finish__timing__setup__tns": -8.00,
        "detailedroute__route__wirelength": 7200,
        "detailedroute__route__drc_errors": 0,
        "detailedroute__antenna__violating__nets": 0,
        "detailedplace__design__violations": 0,
        "total_elapsed_seconds": 100.0,
    }
    values.update(overrides)
    return FlowMetrics(values)


class MetricsTest(unittest.TestCase):
    def test_improved_candidate_has_positive_score(self):
        baseline = metrics()
        candidate = metrics(
            **{
                "finish__timing__setup__ws": -0.10,
                "finish__timing__setup__tns": -6.0,
                "detailedroute__route__wirelength": 7000,
                "total_elapsed_seconds": 90,
            }
        )
        self.assertEqual(verify_correctness(candidate, baseline), [])
        self.assertGreater(score_candidate(candidate, baseline), 0)

    def test_physical_violations_reject_candidate(self):
        baseline = metrics()
        candidate = metrics(**{"detailedroute__route__drc_errors": 1})
        self.assertTrue(verify_correctness(candidate, baseline))

    def test_missing_metric_rejects_candidate(self):
        baseline = metrics()
        candidate = FlowMetrics({})
        self.assertTrue(verify_correctness(candidate, baseline))
