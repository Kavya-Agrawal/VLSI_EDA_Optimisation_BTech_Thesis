"""Command line entry point for preparing and evolving OptMirror policies."""

from __future__ import annotations

import argparse
import json
from pathlib import Path

from .candidate import MirrorPolicy
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
    verify = actions.add_parser(
        "verify", help="rerun a training-promoted policy on held-out ORFS designs"
    )
    verify.add_argument("--candidate", required=True, help="candidate ID from archive.jsonl")
    verify.add_argument(
        "--design",
        action="append",
        choices=("aes", "ibex"),
        help="held-out Nangate45 design; defaults to both aes and ibex",
    )
    return parser


def _load_archived_policy(archive: Path, candidate_id: str) -> MirrorPolicy:
    if not archive.exists():
        raise FileNotFoundError(f"evolution archive does not exist: {archive}")
    for line in archive.read_text().splitlines():
        record = json.loads(line)
        if record["policy"].get("identifier") == candidate_id:
            return MirrorPolicy.from_dict(record["policy"])
    raise ValueError(f"candidate {candidate_id!r} is not present in {archive}")


def main() -> int:
    args = _parser().parse_args()
    config = ExperimentConfig.load(args.config)
    evaluator = FlowEvaluator(config)
    if args.action == "prepare":
        evaluator.prepare()
        print(json.dumps({"source_worktree": str(evaluator.workspace.source_dir)}))
        return 0

    archive = config.workspace.parent / ".evolution" / "archive.jsonl"
    if args.action == "verify":
        policy = _load_archived_policy(archive, args.candidate)
        selected_designs = args.design or ["aes", "ibex"]
        reports = []
        for design in selected_designs:
            held_out = config.with_design(
                design_config=f"designs/nangate45/{design}/config.mk",
                rules_json=f"designs/nangate45/{design}/rules-base.json",
                platform="nangate45",
                design_name=design,
            )
            held_out_evaluator = FlowEvaluator(held_out)
            baseline = held_out_evaluator.evaluate(MirrorPolicy.baseline())
            candidate = held_out_evaluator.evaluate(policy, baseline)
            reports.append(
                {
                    "design": design,
                    "baseline_valid": baseline.valid,
                    "candidate_valid": candidate.valid,
                    "promotion": candidate.promotion,
                    "directory": str(candidate.directory),
                }
            )
        print(
            json.dumps(
                {
                    "candidate": policy.identifier,
                    "held_out_reports": reports,
                    "all_held_out_promotable": all(
                        report["candidate_valid"]
                        and report["promotion"]
                        and report["promotion"]["promotable"]
                        for report in reports
                    ),
                    "automatic_source_merge": False,
                },
                indent=2,
            )
        )
        return 0

    if args.generations < 1 or args.population < 1:
        raise ValueError("generations and population must both be positive")
    run = EvolutionRun(evaluator, archive, config.seed)
    results = run.execute(generations=args.generations, population=args.population)
    ranked = [item for item in results if item.score is not None]
    best = max(ranked, key=lambda item: item.score) if ranked else None
    promoted = [
        item
        for item in ranked
        if item.promotion is not None and item.promotion["promotable"]
    ]
    print(
        json.dumps(
            {
                "archive": str(archive),
                "best_observed": None
                if best is None
                else {"candidate": best.policy.identifier, "score": best.score},
                "training_promoted_candidates": [item.policy.identifier for item in promoted],
                "next_step": "Run verify on each training-promoted candidate before review.",
                "automatic_source_merge": False,
                "valid_candidates": sum(item.valid for item in results),
            },
            indent=2,
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
