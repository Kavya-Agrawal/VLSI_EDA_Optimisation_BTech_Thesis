"""Run from repository root: python3 -m openroad_timing_evolution --help."""
import argparse
import json
from pathlib import Path
import random
import sys

from . import kernel
from .policy import Policy, mutate
from .runner import Campaign, load_config
from .workspace import ROOT, Workspace, output


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--config",type=Path,default=ROOT/"config/smoke.json")
    sub = parser.add_subparsers(dest="command",required=True)
    sub.add_parser("doctor")
    sub.add_parser("prepare")
    sub.add_parser("baseline")
    sub.add_parser("selftest")
    p = sub.add_parser("propose")
    p.add_argument("--output",type=Path,required=True)
    p.add_argument("--seed",type=int,default=41)
    p.add_argument("--parent",type=Path)
    p = sub.add_parser("check")
    p.add_argument("candidate",type=Path)
    p = sub.add_parser("evaluate")
    p.add_argument("candidate",type=Path)
    p = sub.add_parser("evolve")
    p.add_argument("--generations",type=int,default=3)
    p.add_argument("--population",type=int,default=4)
    args = parser.parse_args()
    if args.command=="selftest":
        import unittest
        suite = unittest.defaultTestLoader.discover(str(ROOT/"tests"))
        if suite.countTestCases() == 0:
            raise RuntimeError("no tests discovered")
        return 0 if unittest.TextTestRunner(verbosity=2).run(suite).wasSuccessful() else 1
    if args.command=="propose":
        policy = mutate(Policy.read(args.parent) if args.parent else Policy.stock(),random.Random(args.seed))
        args.output.write_text(json.dumps(policy.data(),indent=2)+"\n")
        print(policy.id)
        return 0
    if args.command=="check":
        policy = Policy.read(args.candidate)
        print(json.dumps(kernel.check(policy,ROOT/"work/kernel"/policy.id),indent=2))
        return 0
    config = load_config(args.config)
    if args.command=="doctor":
        ws = Workspace(config)
        print(json.dumps({"image_id":ws.image,"openroad_revision":config["openroad_revision"],
                          "orfs_revision":config["orfs_revision"],"workspace":str(ws.work)},indent=2))
        ws.execute(["cmake","--version"],ws.work/"doctor-cmake.log",timeout=60)
        ws.execute(["yosys","-V"],ws.work/"doctor-yosys.log",timeout=60)
        return 0
    if args.command=="prepare":
        Workspace(config).prepare()
        return 0
    campaign = Campaign(config)
    print(f"Evidence directory: {campaign.directory}",flush=True)
    if args.command=="baseline":
        campaign.write("baseline.json",campaign.baseline(config["train"]))
    elif args.command=="evaluate":
        from .metrics import assess
        baseline = campaign.baseline(config["train"])
        policy = Policy.read(args.candidate)
        if not policy.enabled:
            raise ValueError("evaluate expects an enabled candidate policy; use baseline for stock")
        rows = campaign.evaluate(policy,config["train"])
        campaign.write("result.json",assess(baseline,rows,config["train"],config))
    else:
        from .search import evolve
        print(json.dumps(evolve(campaign,args.generations,args.population),indent=2))
    return 0


if __name__=="__main__":
    try:
        sys.exit(main())
    except Exception as exc:
        print(f"REJECTED: {exc}",file=sys.stderr)
        sys.exit(1)
