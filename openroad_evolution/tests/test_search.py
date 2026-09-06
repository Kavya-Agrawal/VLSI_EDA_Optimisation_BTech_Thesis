from pathlib import Path
import tempfile
import unittest

from openroad_evolution.candidate import MirrorPolicy
from openroad_evolution.evaluator import Evaluation
from openroad_evolution.search import EvolutionRun, mutate


class SearchTest(unittest.TestCase):
    def test_mutation_is_bounded_and_enabled(self):
        import random

        child = mutate(MirrorPolicy(1.0, 0.0, 0.0), random.Random(3))
        child.validate()
        self.assertTrue(child.enabled)
        self.assertNotEqual(child.identifier, MirrorPolicy(1.0, 0.0, 0.0).identifier)

    def test_archive_captures_baseline_and_candidates(self):
        class FakeEvaluator:
            raw = {
                "finish__timing__setup__ws": -0.2,
                "finish__timing__setup__tns": -8,
                "detailedroute__route__wirelength": 7200,
                "detailedroute__route__drc_errors": 0,
                "detailedroute__antenna__violating__nets": 0,
                "detailedplace__design__violations": 0,
                "total_elapsed_seconds": 100,
            }

            def evaluate(self, policy, baseline=None):
                raw = dict(self.raw)
                if policy.enabled:
                    raw["finish__timing__setup__ws"] += 0.01
                return Evaluation(policy, True, 0.1 if baseline else None, [], raw, Path("."))

        with tempfile.TemporaryDirectory() as temp:
            archive = Path(temp) / "archive.jsonl"
            results = EvolutionRun(FakeEvaluator(), archive, 5).execute(generations=1, population=2)
            self.assertEqual(len(results), 3)
            self.assertEqual(len(archive.read_text().splitlines()), 3)
