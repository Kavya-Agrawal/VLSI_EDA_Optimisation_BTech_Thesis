"""PV-Evolve demo utilities for Makefile targets."""
from __future__ import annotations

import sys


def demo_contract():
    from .contract import Layer, LAYER_SPEC, Domain
    print("Physical Verification Correctness Contract (PVCC)")
    print("=" * 60)
    for layer in Layer:
        spec = LAYER_SPEC[layer]
        abc = "YES" if spec["abc_equivalent"] else "no"
        print(f"{layer.value:36s} [{spec['domain'].value:12s}] ABC={abc}")
        print(f"  {spec['description']}")
    print()
    print("Properties: fail-closed, evidence-bearing, composable, auditable")


def demo_attribution():
    from .path_attribution import (CriticalPath, attribute_paths,
                                   classify_path, format_attribution)
    paths = [
        CriticalPath("ep1", -0.15, 2.1, 20, 0.08, 12, 0.12, 45),
        CriticalPath("ep2", -0.08, 1.8, 8, 0.03, 15, 0.06, 25),
        CriticalPath("ep3", -0.22, 2.5, 3, 0.09, 4, 0.15, 12),
    ]
    program = ["load_pressure", "fanout_shock", "late_path_focus", "stability_damper"]
    print("Synthetic critical paths:")
    for p in paths:
        feats = classify_path(p)
        print(f"  {p.endpoint}: slack={p.slack_ns:.3f}ns features={feats}")
    print()
    weights = attribute_paths(paths, program)
    print(format_attribution(weights, program))


def demo_compare():
    from .contract import compare_to_abc
    cmp = compare_to_abc()
    print("PV-Evolve PVCC vs Self-Evolved ABC CEC")
    print("=" * 55)
    print(f"Verification layers:  PVCC={cmp['pvcc_layers']}  ABC={cmp['abc_layers']}")
    print(f"Domains covered:      PVCC={cmp['pvcc_domains']}")
    print(f"                      ABC={cmp['abc_domains']}")
    print()
    print("Novel layers (not in ABC):")
    for nl in cmp["pvcc_novel_layers"]:
        print(f"  {nl['layer']:36s} {nl['reason']}")
    print()
    print("Contract properties:")
    for k, v in cmp["properties"].items():
        print(f"  {k:20s} {v}")


def demo_mutation():
    import random
    from .policy import Policy, mutate
    from .path_attribution import (CriticalPath, attribute_paths,
                                   format_attribution)
    paths = [
        CriticalPath("ep1", -0.15, 2.1, 20, 0.08, 12, 0.12, 45),
        CriticalPath("ep2", -0.08, 1.8, 8, 0.03, 15, 0.06, 25),
    ]
    program = ["load_pressure", "fanout_shock", "late_path_focus", "stability_damper"]
    parent = Policy.from_dict({"enabled": True, "program": program})
    weights = attribute_paths(paths, program)
    print(f"Parent: {program}")
    print(format_attribution(weights, program))
    print()
    rng = random.Random(42)
    print("Guided mutations (p_guided=0.8):")
    for i in range(5):
        child = mutate(parent, rng, attribution_weights=weights, p_guided=0.8)
        print(f"  #{i+1}: {child.data()['program']}")
    print()
    print("Blind mutations (no attribution):")
    rng = random.Random(42)
    for i in range(5):
        child = mutate(parent, rng)
        print(f"  #{i+1}: {child.data()['program']}")


if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else "all"
    if cmd == "contract":
        demo_contract()
    elif cmd == "attribution":
        demo_attribution()
    elif cmd == "compare":
        demo_compare()
    elif cmd == "mutation":
        demo_mutation()
    elif cmd == "all":
        demo_contract()
        print("\n" + "─" * 60 + "\n")
        demo_attribution()
        print("\n" + "─" * 60 + "\n")
        demo_compare()
        print("\n" + "─" * 60 + "\n")
        demo_mutation()
    else:
        print(f"Unknown command: {cmd}")
        print("Usage: python -m openroad_timing_evolution.pv_demo [contract|attribution|compare|mutation|all]")
        sys.exit(1)
