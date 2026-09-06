import unittest

from openroad_evolution.metrics import (
    FlowMetrics,
    assess_promotion,
    median_metrics,
    score_candidate,
    verify_correctness,
)


def metrics(**overrides):
    values = {
        "finish__timing__setup__ws": -0.20,
        "finish__timing__setup__tns": -8.00,
        "finish__timing__hold__ws": -0.05,
        "finish__timing__hold__tns": -1.00,
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
                "finish__timing__hold__ws": -0.02,
                "finish__timing__hold__tns": -0.50,
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

    def test_median_and_paired_promotion_are_reproducible(self):
        baseline = [metrics() for _ in range(5)]
        candidate = [
            metrics(
                **{
                    "finish__timing__setup__ws": -0.10,
                    "finish__timing__setup__tns": -6.0,
                    "finish__timing__hold__ws": -0.02,
                    "finish__timing__hold__tns": -0.5,
                    "detailedroute__route__wirelength": 7000,
                    "total_elapsed_seconds": 90,
                }
            )
            for _ in range(5)
        ]
        decision = assess_promotion(
            candidate,
            baseline,
            timing_absolute_tolerance=0.0,
            max_relative_wirelength_regression=0.005,
            max_relative_runtime_regression=0.10,
            minimum_lower_bound=0.002,
            bootstrap_samples=2000,
            seed=41,
        )
        self.assertTrue(decision.promotable)
        self.assertGreater(decision.lower_confidence_bound, 0.002)
        self.assertGreater(decision.median_score, 0.0)
        self.assertEqual(median_metrics(candidate).value("runtime"), 90.0)

    def test_one_bad_seed_blocks_promotion(self):
        baseline = [metrics() for _ in range(5)]
        candidate = [metrics(**{"total_elapsed_seconds": 90}) for _ in range(4)]
        candidate.append(metrics(**{"total_elapsed_seconds": 110}))
        decision = assess_promotion(
            candidate,
            baseline,
            timing_absolute_tolerance=0.0,
            max_relative_wirelength_regression=0.005,
            max_relative_runtime_regression=0.10,
            minimum_lower_bound=0.002,
            bootstrap_samples=2000,
            seed=41,
        )
        self.assertFalse(decision.promotable)
        self.assertTrue(any("non-positive" in reason for reason in decision.reasons))
