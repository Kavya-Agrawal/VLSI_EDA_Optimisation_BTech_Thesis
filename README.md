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

## OpenROAD code-evolution runs

Use branch `research/openroad-evolution-suite` for the two real OpenROAD
evolution frameworks:

```bash
git switch research/openroad-evolution-suite
git pull --ff-only --recurse-submodules
git submodule update --init --recursive
make test-placement
make test-timing-evolution
```

Run both frameworks:

```bash
make run-both N=1
make results
```

Run only OptMirror placement:

```bash
make run-placement N=1
make report-placement
```

Run only Resizer timing closure:

```bash
make run-timing N=1
make report-timing-evolution
```

Increase `N` for more new evolution attempts. The archives are append-only:
`N=40` followed by `N=80` gives 120 attempted candidates, not an overwrite.
Result summaries are written to:

- `openroad_evolution/.evolution/summary.md`
- `openroad_timing_evolution/work/memory/summary.md`

The framework evolves generated C++ policy code, not only scalar parameters.
Both experiments use Segmented Semantic Program Evolution with a semantic
relation graph over code blocks. See [`OPENROAD_EVOLUTION_RUNBOOK.md`](OPENROAD_EVOLUTION_RUNBOOK.md)
for the detailed runbook and evidence locations.

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
