# VLSI EDA Optimisation — BTech Thesis

Personal workspace for ML-for-EDA research and tooling, including logic synthesis (ABC), macro placement, and a curated research compendium.

## Quick start

```bash
make doctor
make list
make test
```

The top-level `Makefile` provides the same command interface on every research
branch. See [`PROJECT_GUIDE.md`](PROJECT_GUIDE.md) for the code map, clean branch
names, setup instructions, and framework commands.

## Contents

| Directory | Description |
|-----------|-------------|
| [`abc/`](abc/) | Berkeley ABC — logic synthesis and verification |
| [`macroPlace/`](macroPlace/) | Macro placement projects (challenge framework + ML experiments) |
| [`ml_for_eda_research/`](ml_for_eda_research/) | BTP research compendium: papers, repos, and ABC deep-dive notes |
| [`abc_documentation.txt`](abc_documentation.txt) | Quick links to ABC and OpenROAD resources |

## Upstream sources

- ABC: https://github.com/berkeley-abc/abc
- Macro Place Challenge 2026: https://github.com/partcleda/macro-place-challenge-2026
- Macro Placement ML for EDA: https://github.com/Kavya-Agrawal/Macro_Placement_ML_for_EDA

Large benchmark datasets under `macroPlace/` are excluded from this repo via `.gitignore`. Clone or download them separately when running experiments.

OpenROAD is not vendored here; clone it from https://github.com/The-OpenROAD-Project/OpenROAD when needed.
