# VLSI EDA Optimisation — BTech Thesis

Research code for logic synthesis, physical design, and ML-guided algorithm
evolution using Berkeley ABC and OpenROAD.

## Quick start

```bash
make doctor
make setup
make list
make test
```

The top-level `Makefile` is the common entry point on every research branch.
See [`PROJECT_GUIDE.md`](PROJECT_GUIDE.md) for the directory map, branch map,
and commands for each framework.

## Contents

| Directory | Description |
|-----------|-------------|
| [`abc/`](abc/) | Berkeley ABC — logic synthesis and verification |
| [`macroPlace/`](macroPlace/) | Macro placement projects (challenge framework + ML experiments) |
| [`ml_for_eda_research/`](ml_for_eda_research/) | BTP research compendium: papers, repos, and ABC deep-dive notes |
| [`external/OpenROAD/`](external/OpenROAD/) | Pinned official OpenROAD source, with nested submodules |
| [`external/OpenROAD-flow-scripts/`](external/OpenROAD-flow-scripts/) | Pinned official RTL-to-GDSII flow source and tool submodules |
| [`openroad_evolution/`](openroad_evolution/) | Reproducible algorithm-evolution framework for detailed placement |
| [`openroad_timing_evolution/`](openroad_timing_evolution/) | Correctness-gated resizer timing evolution framework |
| [`openroad_ml/`](openroad_ml/) | ML experiments for OpenROAD congestion, timing, and gate sizing |
| [`abc_documentation.txt`](abc_documentation.txt) | Quick links to ABC and OpenROAD resources |

## Upstream sources

- ABC: https://github.com/berkeley-abc/abc
- Macro Place Challenge 2026: https://github.com/partcleda/macro-place-challenge-2026
- Macro Placement ML for EDA: https://github.com/Kavya-Agrawal/Macro_Placement_ML_for_EDA

Large benchmark datasets under `macroPlace/` are excluded from this repo via `.gitignore`. Clone or download them separately when running experiments.

OpenROAD and OpenROAD-flow-scripts are included as pinned Git submodules. Initialize them after cloning this repository:

```sh
git submodule update --init --recursive
```

The evolution packages modify only bounded generated policies in isolated
workspaces, then gate candidates with tests and full ORFS evidence. Read the
framework's own README before starting a long experiment.
