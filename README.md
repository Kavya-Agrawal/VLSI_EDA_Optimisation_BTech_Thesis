# PV-Evolve: Path-Verified Evolution of OpenROAD Physical Design Code

**B.Tech Thesis — Vedant Sinha, IIT Guwahati**

A framework for evolving OpenROAD physical design code with formal multi-domain
correctness guarantees. Two novel contributions:

1. **Physical Verification Correctness Contract (PVCC)** — 6-layer fail-closed
   verification spanning structural, geometric, temporal, electrical, and logical domains.
2. **Timing-Path-Guided Mutation (TPGM)** — STA critical paths feed back into the
   mutation operator, biasing changes toward blocks influencing timing.

## Quick Start

```bash
git submodule update --init --recursive
make test-timing-evolution    # run unit tests
make pv-all                   # run all PV-Evolve demos
make pv-live                  # run real OpenROAD evolution (requires Docker)
```

## Repository Structure

```
├── openroad_timing_evolution/   # PV-Evolve framework (Resizer + PVCC + TPGM)
│   ├── contract.py              # 6-layer PVCC formalization
│   ├── path_attribution.py      # TPGM path-to-block attribution
│   ├── policy.py                # SSPE mutation with guided selection
│   ├── search.py                # Evolutionary search loop
│   ├── runner.py                # Real OpenROAD/ORFS evaluation
│   ├── live_demo.py             # Live demo with terminal output
│   ├── results/                 # Results, code changes, evidence
│   └── presentation/            # Paper (LaTeX) + presentation (PPTX)
│
├── openroad_evolution/          # OptMirror detailed placement evolution
│   └── src/openroad_evolution/  # OptMirror candidate framework
│
├── external/
│   ├── OpenROAD/                # Pinned OpenROAD source (submodule)
│   └── OpenROAD-flow-scripts/   # Pinned ORFS (submodule)
│
├── archive/                     # Previous research, docs, ABC, ML experiments
├── Makefile                     # All commands
└── README.md
```

## Commands

| Command | Description |
|---------|-------------|
| `make pv-report` | **Print executive statistical report & PVCC contract status** |
| `make pv-all` | Run all PVCC + TPGM demos |
| `make pv-contract` | Show 6-layer PVCC specification |
| `make pv-attribution` | Demo TPGM path attribution |
| `make pv-compare` | PVCC vs ABC CEC comparison |
| `make pv-mutation` | Guided vs blind mutation demo |
| `make pv-live` | **Run real OpenROAD evolution** (Docker required) |
| `make pv-live-quick` | Quick single-iteration demo |
| `make test-timing-evolution` | Run unit tests |

## Results & Code Artifacts (Direct Access)

The final evaluation dataset, source files, and 3,500 generated candidate policy variants are tracked directly in the repository:

- 📂 [**`OPENROAD_EVOLUTION_FINAL/`**](./OPENROAD_EVOLUTION_FINAL) — Main evaluation results and dashboard.
- 📄 [**Original Baseline Sources (`_old`)**](./OPENROAD_EVOLUTION_FINAL/sources/old) — Original baseline C++ source files (`SetupLegacyBase.cc`, `RecoverPower.cc`, `RepairHold.cc`, `Clock.cpp`, `TritonCTS.cpp`, etc.).
- 📄 [**Evolved New Sources (`_new`)**](./OPENROAD_EVOLUTION_FINAL/sources/new) — Evolved new C++ source files with policy modifications.
- 🔀 [**Unified Source Diffs**](./OPENROAD_EVOLUTION_FINAL/diffs) — Side-by-side patch diffs between baseline and evolved code.
- 🧬 [**3,500 Candidate Variants**](./OPENROAD_EVOLUTION_FINAL/candidate_code) — All 3,500 policy headers (`<hash>_new.h`) generated across generations.
- 🌐 [**Interactive Web Dashboard**](https://kavya-agrawal.github.io/VLSI_EDA_Optimisation_BTech_Thesis/archive/OPENROAD_EVOLUTION_FINAL/index.html) — Online interactive exploration of all 3,500 variants.

## Key Results

| Metric | Value |
|--------|-------|
| P99 WNS improvement | **4.88%** |
| Mean WNS improvement | 1.15% |
| TPGM convergence speedup | 1.9× |
| PVCC verification layers | 6 (vs 1 in Self-Evolved ABC) |
| Total candidates evaluated | 3,500 |

Results are in `openroad_timing_evolution/results/`:
- `timing_improvement_summary.json` — full statistics
- `pvcc_verification_evidence.json` — 6-layer evidence for champion
- `critical_path_traces.json` — top-20 STA paths with attribution
- `top_code_changes.json` — top 5 evolved candidates with parameter diffs
- `code_changes/` — actual before/after C++ header files
- `champion_code_change.cpp` — annotated stock vs evolved priority function

## Evolution Targets

| Agent | Target File | Status |
|-------|-------------|--------|
| **Resizer** | `src/rsz/src/policy/SetupLegacyBase.cc` | Fully implemented |
| **CTS** | `src/cts/src/LearningPolicyConfig.h` | Pipeline-ready, 3500 candidates evaluated |
| **OptMirror** | `src/dpl/src/OptMirror.cpp` | Pipeline-ready |

The pipeline (PVCC + TPGM + SSPE) is stage-agnostic — the same contract and
mutation mechanism apply to any OpenROAD subsystem.

## References

- Self-Evolved ABC (arXiv:2604.15082) — base paper being adapted
- VERI-SURE (arXiv:2601.19747) — contract-based RTL verification
- VPR-Evolve (arXiv:2607.24998) — multi-agent FPGA evolution
- EvoDRC (arXiv:2607.20019) — self-evolving DRC repair
