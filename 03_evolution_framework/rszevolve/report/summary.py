"""Text reports: `make status` and `make report`."""
from __future__ import annotations

from ..budget import Budget
from ..config import PATHS, Knobs
from ..eval.baseline import load_baseline
from ..knowledge.ledger import champion_record, load_lineage
from ..util import read_json


def print_status() -> None:
    lin = load_lineage()
    its = lin.get("iterations", [])
    champ = champion_record()
    b = Budget.load(PATHS.agent_data / "budget.json")
    print(f"iterations recorded: {len(its)}   accepted: {sum(1 for i in its if i.get('accepted'))}   "
          f"rejected: {sum(1 for i in its if i.get('status') == 'rejected')}   build_failed: {sum(1 for i in its if i.get('status') == 'build_failed')}   crashed: {sum(1 for i in its if i.get('status') == 'crashed')}")
    print(f"champion: iteration {champ.get('iteration', 0)} (score vs baseline {champ.get('score_vs_baseline') or 0:+.5f})  {str(champ.get('hypothesis') or 'original')[:100]}")
    print(f"spend: {b.summary()}")
    for i in its[-8:]:
        print(f"  #{i.get('iteration'):>3} {i.get('status', ''):12s} {i.get('cluster', ''):15s} {float(i.get('score_vs_champion') or 0):+.5f}  {str(i.get('title') or i.get('error') or '')[:70]}")


def print_report() -> None:
    knobs = Knobs.load()
    base = load_baseline().get("variants", {}).get(knobs.sdc_variant, {})
    print(f"== Baseline ({knobs.sdc_variant}) ==")
    for k, a in sorted(base.items()):
        if a.get("ok"):
            print(f"  {k:18s} WNS {a['pre']['wns_setup']:+.4f} -> {a['post']['wns_setup']['mean']:+.4f}   TNS {a['pre']['tns_setup']:+.3f} -> {a['post']['tns_setup']['mean']:+.3f}   period {a['period_ns']}")
    print("\n== Iterations ==")
    lin = load_lineage()
    per = Budget.load(PATHS.agent_data / "budget.json").per_iteration()
    print(f"  {'#':>3} {'status':12s} {'cluster':15s} {'vs champ':>9s} {'vs base':>9s} {'USD':>6s}  per-design WNS (cand vs ref)")
    for i in lin.get("iterations", []):
        pd = i.get("per_design") or {}
        cells = "  ".join(f"{k.split('/')[-1]}:{v['wns_cand']:+.3f}/{v['wns_ref']:+.3f}" for k, v in pd.items())
        usd = per.get(int(i.get("iteration", 0)), {}).get("usd", 0.0)
        print(f"  {i.get('iteration'):>3} {i.get('status', ''):12s} {i.get('cluster', ''):15s} {float(i.get('score_vs_champion') or 0):+9.5f} {float(i.get('score_vs_baseline') or 0):+9.5f} {usd:6.2f}  {cells}")
    print()
    print_status()
