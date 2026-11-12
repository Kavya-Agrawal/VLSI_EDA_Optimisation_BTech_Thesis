"""`python -m rszevolve <command>` — every Makefile target calls one of these."""
from __future__ import annotations

import argparse
import sys
from pathlib import Path

from .config import PATHS, Knobs, designs_for_tier
from .util import log


def _knobs(args: argparse.Namespace) -> Knobs:
    return Knobs.load(overrides={k: getattr(args, k, None) for k in ("repair_timing_args", "path_count", "sdc_variant")})


def cmd_checkpoints(args: argparse.Namespace) -> int:
    from .eval.checkpoints import make_tier
    make_tier(args.tier, _knobs(args), only=args.only, force=args.force, calibrate=not args.no_calibrate)
    return 0


def cmd_baseline(args: argparse.Namespace) -> int:
    from .eval.baseline import run_baseline
    variants = tuple(args.variants.split(",")) if args.variants else ("stressed", "nominal")
    run_baseline(args.tier, _knobs(args), replicates=args.replicates, variants=variants, only=args.only)
    return 0


def cmd_evaluate(args: argparse.Namespace) -> int:
    from .eval.candidate import evaluate_rsz_tree
    v = evaluate_rsz_tree(Path(args.rsz).resolve(), _knobs(args), tier=args.tier, replicates=args.replicates, tag=args.tag,
                          skip_build=args.skip_build)
    return 0 if v.accepted or args.no_fail else 1


def cmd_graphify(args: argparse.Namespace) -> int:
    from .context.graphify_run import run_graphify
    return run_graphify(scope=args.scope, knobs=_knobs(args))


def cmd_context(args: argparse.Namespace) -> int:
    from .context.build_context import build_context
    return build_context(_knobs(args), only=args.only)


def cmd_evolve(args: argparse.Namespace) -> int:
    from .orchestrator import evolve
    return evolve(iterations=args.iterations, budget_usd=args.budget_usd, max_tokens=args.max_tokens, tier=args.tier,
                  replicates=args.replicates, resume=args.resume, knobs=_knobs(args), cluster=args.cluster)


def cmd_report(args: argparse.Namespace) -> int:
    from .report.summary import print_report
    print_report()
    return 0


def cmd_viz(args: argparse.Namespace) -> int:
    from .report.viz import render_all
    render_all()
    return 0


def cmd_status(args: argparse.Namespace) -> int:
    from .report.summary import print_status
    print_status()
    return 0


def main(argv: list[str] | None = None) -> int:
    p = argparse.ArgumentParser(prog="rszevolve", description=__doc__)
    sub = p.add_subparsers(dest="cmd", required=True)

    s = sub.add_parser("checkpoints", help="ORFS up to detailed placement -> 04_benchmarks/designs")
    s.add_argument("--tier", default="A"); s.add_argument("--only", nargs="*"); s.add_argument("--force", action="store_true")
    s.add_argument("--no-calibrate", action="store_true"); s.set_defaults(fn=cmd_checkpoints)

    s = sub.add_parser("baseline", help="stock openroad on checkpoints -> 05_baseline_results")
    s.add_argument("--tier", default="A"); s.add_argument("--replicates", type=int, default=3); s.add_argument("--only", nargs="*")
    s.add_argument("--variants", default=None, help="comma list, default stressed,nominal"); s.set_defaults(fn=cmd_baseline)

    s = sub.add_parser("evaluate", help="build + gate + evaluate an rsz tree against baseline/champion")
    s.add_argument("--rsz", required=True); s.add_argument("--tier", default="A"); s.add_argument("--replicates", type=int, default=2)
    s.add_argument("--tag", default="manual"); s.add_argument("--skip-build", action="store_true"); s.add_argument("--no-fail", action="store_true")
    s.set_defaults(fn=cmd_evaluate)

    s = sub.add_parser("graphify", help="knowledge graphs into 08_graphify")
    s.add_argument("--scope", default="all", choices=["all", "full", "rsz"]); s.set_defaults(fn=cmd_graphify)

    s = sub.add_parser("context", help="generate 09_agent_context")
    s.add_argument("--only", nargs="*", help="subset: big_picture files algorithms clusters glossary"); s.set_defaults(fn=cmd_context)

    s = sub.add_parser("evolve", help="run the plan->code->build->evaluate loop")
    s.add_argument("--iterations", type=int, default=1); s.add_argument("--budget-usd", type=float, default=0.0)
    s.add_argument("--max-tokens", type=int, default=0); s.add_argument("--tier", default="A"); s.add_argument("--replicates", type=int, default=2)
    s.add_argument("--resume", action="store_true"); s.add_argument("--cluster", default=None, help="force a cluster for the next iteration")
    s.set_defaults(fn=cmd_evolve)

    for name, fn in (("report", cmd_report), ("viz", cmd_viz), ("status", cmd_status)):
        s = sub.add_parser(name); s.set_defaults(fn=fn)

    for s_ in sub.choices.values():
        s_.add_argument("--repair-timing-args", dest="repair_timing_args", default=None)
        s_.add_argument("--path-count", dest="path_count", type=int, default=None)
        s_.add_argument("--sdc-variant", dest="sdc_variant", default=None)

    args = p.parse_args(argv)
    try:
        return int(args.fn(args) or 0)
    except KeyboardInterrupt:
        log("interrupted")
        return 130


if __name__ == "__main__":
    sys.exit(main())
