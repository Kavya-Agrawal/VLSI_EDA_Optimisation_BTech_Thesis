# Project guide

This repository is a BTech thesis workspace for logic synthesis, physical
design, and ML/evolution experiments. Run commands from the repository root.

## First-time setup

```bash
git clone --recurse-submodules https://github.com/Kavya-Agrawal/VLSI_EDA_Optimisation_BTech_Thesis.git
cd VLSI_EDA_Optimisation_BTech_Thesis
make doctor
make setup
make list
make test
```

Python/ML experiments may need their local `requirements.txt`; `make test`
clearly skips a missing optional ML stack instead of installing it silently.
OpenROAD full flows also require the setup documented in
`OPENROAD_WORKFLOW.md`; the quick unit and smoke tests do not build OpenROAD.

## Where the code is

| Path | Purpose |
| --- | --- |
| `abc/` | Berkeley ABC source and branch-specific SYNAPSE/POLYPHONY experiments |
| `openroad_evolution/` | Safe detailed-placement (OptMirror) evolution framework |
| `openroad_timing_evolution/` | Resizer path-driver timing evolution framework |
| `openroad_ml/` | Congestion CNN plus branch-specific timing-GNN and RL gate-sizing work |
| `external/` | Pinned OpenROAD and OpenROAD-flow-scripts submodules |
| `macroPlace/` | Macro-placement projects and benchmark tooling |
| `abc_docs/`, `*_latex_docs/` | Learning material and thesis-oriented documentation |
| `ml_for_eda_research/`, `papers/` | Literature notes and reference papers |
| `output/` | Deliberately retained presentation/final artifacts |

Generated framework runs live below each framework's ignored `work/` or
`.evolution/` directory. They are evidence/build products, not source code.

## One command interface

```bash
make help
make list
make test
make framework FRAMEWORK=placement
make branch FRAMEWORK=timing-gnn
```

`make list` is branch-aware: its last column says which frameworks exist in
the current checkout. If one is absent, `make branch FRAMEWORK=<name>` switches
to the cleanly named branch containing it.

Common experiment commands:

```bash
# Fast correctness checks
make test-placement
make test-timing-evolution
make test-congestion-cnn

# Full evolution campaigns (long-running; require OpenROAD/ORFS dependencies)
make prepare-placement
make evolve-placement GENERATIONS=3 POPULATION=4
make verify-placement CANDIDATE=<candidate-id>

make doctor-timing-evolution
make baseline-timing-evolution
make evolve-timing-evolution GENERATIONS=3 POPULATION=4

# Other frameworks, when on their branch
make test-rl-gatesize
make test-timing-gnn
make test-synapse
make test-polyphony

# Supporting tools
make abc-build JOBS=8
make openroad-flow DESIGN_CONFIG=designs/nangate45/gcd/config.mk
```

## Branches

- `main`: stable overview and common research material.
- `research/openroad-evolution-suite`: placement evolution, timing evolution,
  congestion CNN, presentations, and pinned OpenROAD sources.
- `research/openroad-rl-gate-sizing`: RL gate-sizing experiment.
- `research/openroad-timing-gnn`: timing/slack GNN experiment.
- `research/abc-synapse`: neural-assisted ABC optimization.
- `research/abc-polyphony`: diverse generative ABC synthesis.
- `research/openroad-ml-landscape`: research survey and branch map.
- `research/openroad-placement-evolution` and
  `research/openroad-placement-safety`: retained milestones for the placement
  evolution work.
- `archive/openroad-sources` and `archive/initial-import`: historical snapshots.

Use `git switch <branch>` directly if you prefer. Do not commit generated
OpenROAD builds or experiment run directories.
