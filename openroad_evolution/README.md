# OpenROAD OptMirror Evolution

This is a compact, end-to-end algorithm-evolution experiment for a real
OpenROAD placement heuristic. It is intentionally small enough for a BTP yet
it is not a toy simulator: every admitted candidate is compiled into
OpenROAD, must pass upstream detailed-placement regressions, and is evaluated
by a full OpenROAD-flow-scripts (ORFS) RTL-to-GDSII run.

## Target selected from OpenROAD

The target is `external/OpenROAD/src/dpl/src/OptMirror.cpp`, specifically the
ordering of candidates in `OptimizeMirroring::mirrorCandidates`.

`optimize_mirroring` flips a standard cell about the Y axis only when the
change does not worsen its local HPWL. Candidate order matters because every
accepted flip updates net boxes used by later decisions. This makes the
ordering a compact, non-commutative placement heuristic with real downstream
effects on routing and timing.

The evolving artifact is a generated C++ header, typically 25 lines. It ranks
legal mirror candidates using a weighted expression over local HPWL, cell pin
degree, and stable instance ID. It cannot move a cell, alter connectivity, or
bypass OpenDP's cell-edge-spacing and non-increasing-HPWL guards.

`patches/opt_mirror_policy.patch` adds the fixed seam. The runner applies it
only in an isolated Git worktree and initializes the exact nested source
submodules there; the pinned `external/OpenROAD` submodule is never modified.

## Correctness and QoR contract

Candidates are evaluated serially and a candidate enters the parent pool only
if all of the following pass:

1. OpenROAD compiles.
2. Upstream `dpl.mirror1`, `mirror2`, `mirror3`, and
   `mirror_edge_spacing` regression tests pass.
3. ORFS completes `all metadata` for `nangate45/gcd`, which covers synthesis,
   placement, CTS, global/detailed routing, finishing and signoff reports.
4. METRICS2.1 reports zero detailed-placement violations, and detailed-route
   DRC and antenna violations do not exceed the stock baseline.
5. The candidate has finite final setup WNS/TNS, routed wirelength, and total
   elapsed time.

The score is `0.45*WNS + 0.35*TNS - 0.15*wirelength - 0.05*runtime`, expressed
as normalized improvement over the stock baseline. Timing closure is therefore
the primary optimization target; routing quality and practical runtime remain
visible. Failed candidates are retained with their source, logs, metrics and
rejection reason, rather than silently discarded.

## One-time tool setup

All upstream source code is already pinned by this repository's submodules.
After cloning the BTP repository, initialize it once:

```sh
git submodule update --init --recursive
```

The full flow additionally needs the official ORFS build dependencies. On a
supported Linux host, use the upstream setup and local build process:

```sh
cd external/OpenROAD-flow-scripts
sudo ./setup.sh
./build_openroad.sh --local
```

This project deliberately does not invoke `sudo` or download a Docker image on
your behalf. Those system-level actions remain explicit. The default evolution
configuration builds its own patched OpenROAD worktree with the dependencies
installed by ORFS, then points ORFS at that candidate executable via
`OPENROAD_EXE`.

## Run an experiment

Run these commands from this directory:

```sh
PYTHONPATH=src python3 -m openroad_evolution.cli --config config/default.json prepare
PYTHONPATH=src python3 -m openroad_evolution.cli --config config/default.json evolve --generations 3 --population 4
```

The default is intentionally conservative: 12 candidate full flows plus the
stock baseline. Increase the population only after verifying the baseline on
your machine. The run is serial because ORFS uses fixed `results/`, `logs/`,
and `reports/` locations for a design.

Generated artifacts are intentionally ignored by Git:

- `work/openroad-source/`: patched isolated OpenROAD worktree and build tree.
- `.evolution/runs/<candidate-id>/`: generated header, compile/regression/flow
  logs, final METRICS2.1 JSON and a decision record.
- `.evolution/archive.jsonl`: append-only search history, including failures.

## Test the framework itself

These fast tests do not build OpenROAD:

```sh
PYTHONPATH=src python3 -m unittest discover -s tests -v
```

Read [`DESIGN.md`](DESIGN.md) for the research rationale, experimental design,
and the direct connections to the four supplied papers.
