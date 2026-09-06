"""Command line entry point for preparing and evolving OptMirror policies."""

from __future__ import annotations

import argparse
import json
from pathlib import Path

from .config import ExperimentConfig
from .evaluator import FlowEvaluator
from .search import EvolutionRun


def _parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--config", default="config/default.json", help="experiment JSON configuration"
    )
    actions = parser.add_subparsers(dest="action", required=True)
    actions.add_parser("prepare", help="create patched isolated OpenROAD worktree")
    evolve = actions.add_parser("evolve", help="run correctness-gated policy evolution")
    evolve.add_argument("--generations", type=int, default=3)
    evolve.add_argument("--population", type=int, default=4)
    return parser


def main() -> int:
    args = _parser().parse_args()
    config = ExperimentConfig.load(args.config)
    evaluator = FlowEvaluator(config)
    if args.action == "prepare":
        evaluator.prepare()
        print(json.dumps({"source_worktree": str(evaluator.workspace.source_dir)}))
        return 0

    archive = config.workspace.parent / ".evolution" / "archive.jsonl"
    run = EvolutionRun(evaluator, archive, config.seed)
    results = run.execute(generations=args.generations, population=args.population)
    best = max((item for item in results if item.score is not None), key=lambda item: item.score)
    print(
        json.dumps(
            {
                "archive": str(archive),
                "best_candidate": best.policy.identifier,
                "best_score": best.score,
                "valid_candidates": sum(item.valid for item in results),
            },
            indent=2,
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
