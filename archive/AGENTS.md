# Agent Context

Read `EVOLUTION_RESEARCH_GUIDE.md` before modifying or describing either
OpenROAD evolution framework. It contains the branch map, exact OpenROAD
targets, search algorithms, correctness contracts, scoring, commands, known
limitations, and evidence locations.

## Canonical Branch

Both frameworks live together on `research/openroad-evolution-suite`:

- `openroad_evolution/`: OpenDP OptMirror candidate-order evolution.
- `openroad_timing_evolution/`: Resizer setup path-driver-order evolution.
- `external/OpenROAD` and `external/OpenROAD-flow-scripts`: pinned submodules.

`research/openroad-placement-evolution` and
`research/openroad-placement-safety` are retained milestones. Do not treat
`feature/*`, `archive/*`, or `main` as the definitive combined implementation.

## Non-Negotiable Technical Facts

1. Neither runtime framework uses an LLM. Proposals come from seeded numeric or
   expression-tree mutation, and deterministic tools evaluate them.
2. OptMirror changes only ordering in
   `src/dpl/src/OptMirror.cpp`; legality and non-increasing-HPWL checks remain
   upstream-owned.
3. Resizer evolution changes only ordering in
   `src/rsz/src/policy/SetupLegacyBase.cc`; target creation, repair operations,
   budgets, checks, and rollback remain upstream-owned.
4. Never widen either candidate's editable source surface without updating the
   integrity contract, tests, research claims, and verification design.
5. Full flows target Linux/WSL. Timing evolution requires Docker and Linux-only
   APIs.
6. Generated `work/` and `.evolution/` directories are evidence/build output
   and must not be committed.

## Known Defect

OptMirror held-out verification currently cannot find archived candidates.
`openroad_evolution/src/openroad_evolution/cli.py::_load_archived_policy()`
looks under `record["policy"]["identifier"]`, while `search.py::_append()`
stores `identifier` at the record's top level. Fix the lookup and add a
regression test before claiming `verify-placement` works.

## Minimum Checks After Changes

```bash
make test-placement
make test-timing-evolution
```

For changes to candidate generation, source integration, evaluation, metrics,
or promotion, also run the appropriate prepare/baseline/full-flow command when
the Linux, Docker, OpenROAD, ORFS, and PDK environment is available. Clearly
state when only fast tests were run.

Do not claim successful QoR evolution merely because framework self-tests
pass. A valid research result requires archived baseline/candidate evidence,
all hard gates, repeated runs, and the configured held-out procedure.
