"""Deterministic evolutionary search with a persistent, auditable archive."""

from __future__ import annotations

from dataclasses import dataclass
import json
from pathlib import Path
import random
from typing import Protocol

from .candidate import MirrorPolicy
from .evaluator import Evaluation


class Evaluator(Protocol):
    def evaluate(self, policy: MirrorPolicy, baseline: Evaluation | None = None) -> Evaluation: ...


def mutate(parent: MirrorPolicy, rng: random.Random) -> MirrorPolicy:
    """Mutate exactly one coefficient; retain a bounded, interpretable policy."""
    weights = [parent.hpwl_weight, parent.degree_weight]
    index = rng.randrange(len(weights))
    weights[index] = max(-5.0, min(5.0, weights[index] + rng.gauss(0.0, 0.75)))
    if not any(weights):
        weights[0] = 1.0
    child = MirrorPolicy(*weights, enabled=True)
    child.validate()
    return child


@dataclass
class EvolutionRun:
    evaluator: Evaluator
    archive_path: Path
    seed: int

    def _append(self, result: Evaluation) -> None:
        self.archive_path.parent.mkdir(parents=True, exist_ok=True)
        with self.archive_path.open("a") as archive:
            archive.write(
                json.dumps(
                    {
                        "policy": result.policy.to_dict(),
                        "identifier": result.policy.identifier,
                        "valid": result.valid,
                        "score": result.score,
                        "reasons": result.reasons,
                        "metrics": result.metrics,
                        "replicas": result.replicas,
                        "promotion": result.promotion,
                    },
                    sort_keys=True,
                )
                + "\n"
            )

    def execute(self, *, generations: int, population: int) -> list[Evaluation]:
        if generations < 1 or population < 1:
            raise ValueError("generations and population must be positive")
        rng = random.Random(self.seed)
        baseline_result = self.evaluator.evaluate(MirrorPolicy.baseline())
        self._append(baseline_result)
        if not baseline_result.valid or baseline_result.metrics is None:
            raise RuntimeError("stock baseline must compile, pass regressions, and finish ORFS")
        completed: list[Evaluation] = [baseline_result]
        parents = [MirrorPolicy(1.0, 0.0, enabled=True)]
        seen = {baseline_result.policy.identifier}
        for _generation in range(generations):
            candidates: list[MirrorPolicy] = []
            while len(candidates) < population:
                child = mutate(rng.choice(parents), rng)
                if child.identifier not in seen:
                    candidates.append(child)
                    seen.add(child.identifier)
            generation_results = [self.evaluator.evaluate(item, baseline_result) for item in candidates]
            for result in generation_results:
                self._append(result)
            completed.extend(generation_results)

            valid = [item for item in completed if item.valid and item.score is not None]
            valid.sort(key=lambda item: item.score, reverse=True)
            parents = [item.policy for item in valid[: max(1, min(4, len(valid)))]]
        return completed
