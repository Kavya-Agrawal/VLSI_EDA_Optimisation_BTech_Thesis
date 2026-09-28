"""Deterministic evolutionary search with a persistent, auditable archive."""

from __future__ import annotations

from dataclasses import dataclass
import json
from pathlib import Path
import random
from typing import Protocol

from .candidate import MirrorPolicy, PROGRAM_OPS, program_segments, related_indices
from .evaluator import Evaluation


class Evaluator(Protocol):
    def evaluate(self, policy: MirrorPolicy, baseline: Evaluation | None = None) -> Evaluation: ...


def mutate(parent: MirrorPolicy, rng: random.Random) -> MirrorPolicy:
    """Mutate generated C++ code while retaining a bounded review surface."""
    for _ in range(100):
        weights = [parent.hpwl_weight, parent.degree_weight]
        program = list(parent.program or ("hpwl_log",))
        action = rng.choice((
            "weight",
            "replace",
            "insert",
            "delete",
            "swap",
            "segment_reverse",
            "segment_duplicate",
            "graph_swap",
            "graph_insert_bridge",
        ))
        if action == "weight":
            index = rng.randrange(len(weights))
            weights[index] = max(-5.0, min(5.0, weights[index] + rng.gauss(0.0, 0.75)))
        elif action == "replace" and program:
            program[rng.randrange(len(program))] = rng.choice(PROGRAM_OPS)
        elif action == "insert" and len(program) < 16:
            program.insert(rng.randrange(len(program) + 1), rng.choice(PROGRAM_OPS))
        elif action == "delete" and len(program) > 1:
            del program[rng.randrange(len(program))]
        elif action == "swap" and len(program) > 1:
            a, b = rng.sample(range(len(program)), 2)
            program[a], program[b] = program[b], program[a]
        elif action == "segment_reverse" and len(program) > 2:
            start, end, _ = rng.choice([s for s in program_segments(program) if s[1] - s[0] > 1])
            program[start:end] = reversed(program[start:end])
        elif action == "segment_duplicate" and len(program) < 16:
            start, end, _ = rng.choice(program_segments(program))
            fragment = program[start:end]
            room = 16 - len(program)
            fragment = fragment[:room]
            program[start:start] = fragment
        elif action == "graph_swap" and len(program) > 1:
            pairs = related_indices(program)
            a, b = rng.choice(pairs) if pairs else rng.sample(range(len(program)), 2)
            program[a], program[b] = program[b], program[a]
        elif action == "graph_insert_bridge" and len(program) < 16:
            pairs = related_indices(program)
            _, b = rng.choice(pairs) if pairs else (0, rng.randrange(len(program)))
            bridge = rng.choice(("mirror_entropy_temper", "hpwl_degree_cross", "fanout_shock_penalty"))
            program.insert(b, bridge)
        child = MirrorPolicy(weights[0], weights[1], enabled=True, program=tuple(program))
        child.validate()
        if child.identifier != parent.identifier:
            return child
    raise RuntimeError("could not generate a source-changing OptMirror mutation")


@dataclass
class EvolutionRun:
    evaluator: Evaluator
    archive_path: Path
    seed: int

    def _load_archive(self) -> list[Evaluation]:
        if not self.archive_path.exists():
            return []
        records: list[Evaluation] = []
        for line in self.archive_path.read_text().splitlines():
            if not line.strip():
                continue
            record = json.loads(line)
            policy = MirrorPolicy.from_dict(record["policy"])
            records.append(
                Evaluation(
                    policy,
                    bool(record.get("valid")),
                    record.get("score"),
                    list(record.get("reasons") or []),
                    record.get("metrics"),
                    Path(record.get("directory", ".")),
                    list(record.get("replicas") or []),
                    record.get("promotion"),
                )
            )
        return records

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
                        "directory": str(result.directory),
                    },
                    sort_keys=True,
                )
                + "\n"
            )

    def execute(self, *, generations: int, population: int) -> list[Evaluation]:
        if generations < 1 or population < 1:
            raise ValueError("generations and population must be positive")
        rng = random.Random(self.seed)
        completed: list[Evaluation] = self._load_archive()
        seen = {item.policy.identifier for item in completed}
        baseline_result = next(
            (
                item
                for item in reversed(completed)
                if not item.policy.enabled and item.valid and item.metrics is not None
            ),
            None,
        )
        if baseline_result is None:
            baseline_result = self.evaluator.evaluate(MirrorPolicy.baseline())
            self._append(baseline_result)
            completed.append(baseline_result)
            seen.add(baseline_result.policy.identifier)
        if not baseline_result.valid or baseline_result.metrics is None:
            raise RuntimeError("stock baseline must compile, pass regressions, and finish ORFS")
        valid_archive = [item for item in completed if item.policy.enabled and item.valid and item.score is not None]
        valid_archive.sort(key=lambda item: item.score, reverse=True)
        parents = (
            [item.policy for item in valid_archive[: max(1, min(4, len(valid_archive)))]]
            or [MirrorPolicy(1.0, 0.0, enabled=True)]
        )
        for _generation in range(generations):
            candidates: list[MirrorPolicy] = []
            while len(candidates) < population:
                for _attempt in range(10_000):
                    child = mutate(rng.choice(parents), rng)
                    if child.identifier not in seen:
                        candidates.append(child)
                        seen.add(child.identifier)
                        break
                else:
                    raise RuntimeError("could not generate a new unseen policy")
            generation_results = [self.evaluator.evaluate(item, baseline_result) for item in candidates]
            for result in generation_results:
                self._append(result)
            completed.extend(generation_results)

            valid = [item for item in completed if item.valid and item.score is not None]
            valid.sort(key=lambda item: item.score, reverse=True)
            parents = [item.policy for item in valid[: max(1, min(4, len(valid)))]]
        return completed
