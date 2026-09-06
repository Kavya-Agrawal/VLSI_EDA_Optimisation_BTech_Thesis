# VLSI EDA Optimisation — BTech Thesis

Personal workspace for ML-for-EDA research and tooling, including logic synthesis (ABC), macro placement, and a curated research compendium.

## Contents

| Directory | Description |
|-----------|-------------|
| [`abc/`](abc/) | Berkeley ABC — logic synthesis and verification |
| [`macroPlace/`](macroPlace/) | Macro placement projects (challenge framework + ML experiments) |
| [`ml_for_eda_research/`](ml_for_eda_research/) | BTP research compendium: papers, repos, and ABC deep-dive notes |
| [`external/OpenROAD/`](external/OpenROAD/) | Pinned official OpenROAD source, with nested submodules |
| [`external/OpenROAD-flow-scripts/`](external/OpenROAD-flow-scripts/) | Pinned official RTL-to-GDSII flow source and tool submodules |
| [`openroad_evolution/`](openroad_evolution/) | Reproducible algorithm-evolution framework for detailed placement |
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

The `openroad_evolution/` package evolves a deliberately small, safe
detailed-placement heuristic and evaluates each candidate through OpenROAD
regressions and a complete ORFS run. See its README before starting an experiment.
