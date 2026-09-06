# BTP experiment design: correctness-gated detailed-placement evolution

## Why this target

`OptimizeMirroring::mirrorCandidates` is the right size for a first
algorithm-evolution project: the changed policy is small and interpretable,
yet the resulting cell orientations feed the normal OpenROAD detailed
placement, global routing, detailed routing, parasitic extraction and OpenSTA
timing path. It is therefore more defensible than optimizing a synthetic
wirelength function, while avoiding the risk and cost of letting an agent edit
the much larger RePlAce or FastRoute engines freely.

The source-level search space is deliberately constrained to a ranking
expression:

```
priority(cell) = a * local_HPWL + b * pin_degree + c * instance_ID
```

The candidate header is real C++ compiled into OpenROAD. `a`, `b`, and `c` are
mutated by a seeded evolutionary search, and every version is saved. This is
algorithm evolution, not a flow-knob sweep: it changes the execution order of
the heuristic decisions inside the OpenROAD placement source code.

## Connection to the supplied papers

- **AlphaEvolve** motivates an evolutionary population of executable source
  candidates and a strong automatic evaluator rather than trusting generated
  code.
- **Autonomous Evolution of EDA Tools / self-evolved ABC** motivates applying
  the loop to an EDA codebase, using compile + correctness + QoR gates and a
  persistent record of outcomes.
- **VPR-Evolve** motivates staging the evaluation around a full P&R flow and
  optimizing timing, routed wirelength and runtime together rather than a
  placement-only proxy.
- **EvoDRC** motivates a strict physical-validity gate and retaining traceable
  successful and unsuccessful experience. Here, upstream edge-spacing tests,
  detailed placement checks, and final DRC/antenna metrics serve that role.

## Evaluation protocol

For a candidate `x` and the stock baseline `b`, the evaluator first applies
hard gates:

```
build(x) AND mirror_regressions(x) AND ORFS_RTL_to_GDS(x)
AND place_violations(x) = 0
AND DRC(x) <= DRC(b)
AND antenna_violations(x) <= antenna_violations(b)
```

Only then is it ranked:

```
S(x) = 0.45 ΔWNS + 0.35 ΔTNS - 0.15 Δrouted_wirelength - 0.05 Δruntime
```

Each delta is normalized by `max(abs(baseline), 1)` so a near-zero metric
cannot dominate simply because of its unit scale. A negative score is valid
but does not become a parent when stronger candidates exist. This distinction
is important: feasibility/correctness is not the same as quality of results.

## Experimental reporting plan

Use at least three independently seeded runs on `nangate45/gcd` for rapid
iteration. Promote the best policy only after rerunning the same candidate on
two held-out ORFS designs (for example `nangate45/aes` and `nangate45/ibex`),
with unchanged gates. Report:

1. Baseline and best-candidate WNS, TNS, routed wirelength, runtime, DRC and
   antenna counts.
2. Median and range across repeat runs, not only the best observed sample.
3. The exact generated `EvolvedMirrorPolicy.h`, commit IDs of OpenROAD and
   ORFS, configuration JSON, and the archive record.
4. Ablations for each ranking feature (`a`, `b`, `c`) and a policy disabled
   baseline, so the result is attributable to algorithmic ordering rather than
   a tool-version or flow-config difference.

## Limitations and next step

This first experiment evolves ordering only, so it is low-risk and practical
but has a small search space. Once it yields a stable baseline, the same
framework can add a second checked policy seam in global routing (for example
net-ordering) and use the same full-flow gates. Do not widen the source region
until the current experiment is reproducible on held-out designs.
