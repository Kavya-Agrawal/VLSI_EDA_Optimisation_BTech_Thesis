# OpenROAD Timing Evolution Framework

This branch adds a bounded algorithm evolution framework for OpenROAD resizer timing closure experiments. The evolved code changes only the ordering policy for setup path driver repair inside `src/rsz/src/policy/SetupLegacyBase.cc`; all candidate logic is generated into `src/rsz/src/policy/EvolvedPathDriverPolicy.h` inside an isolated OpenROAD clone.

The target is WNS/TNS improvement after the full OpenROAD-flow-scripts path. Clock tree results are audited as measured evidence through setup and hold skew metrics, but this first implementation does not evolve CTS code.

## Why this cut was chosen

The resizer path-driver ordering is small enough to evolve safely and still affects timing closure. The framework mutates a tiny expression grammar over normalized load delay, fanout and path position. It never accepts arbitrary C++, Python `eval`, free-form patches, or model-written source files.

Research ideas used:

- AlphaEvolve: executable candidates, cascading evaluation, and a program database of accepted and rejected attempts.
- Autonomous Evolution of EDA Tools: compile and QoR loops around real EDA code instead of synthetic benchmarks.
- VPR-Evolve: pinned baselines, training and held-out designs, repeated seeds, and rejected-history logging.
- EvoDRC: bounded physical-design changes with strict physical correctness checks.
- FunSearch and EoH: small program fragments with automated scoring.

## Safety model

The evaluator fails closed. A candidate only survives when all of these pass:

- Generated C++ header compiles under ASan and UBSan.
- Differential kernel tests match the Python reference ordering.
- OpenROAD builds from pinned local commits in a self-contained clone.
- Fixed upstream resizer regressions are present and pass.
- The complete ORFS flow produces final Verilog, DEF/ODB, SDC, SPEF and GDS artifacts.
- A frozen stock OpenROAD binary performs the independent STA audit.
- Setup and hold WNS/TNS do not regress on any paired run.
- Placement, routing DRC, antenna, max slew, max capacitance and max fanout violations are all zero.
- Yosys equivalence proves final Verilog matches the post-synthesis design.
- KLayout DRC produces a valid zero-violation report.
- The evaluator protocol, audit binary and candidate binary hashes remain unchanged during measurement.

## Commands

Run from the repository root:

```bash
python3 -m openroad_timing_evolution selftest
python3 -m openroad_timing_evolution doctor --config openroad_timing_evolution/config/smoke.json
python3 -m openroad_timing_evolution baseline --config openroad_timing_evolution/config/smoke.json
python3 -m openroad_timing_evolution evolve --config openroad_timing_evolution/config/smoke.json --generations 3 --population 4
```

The default smoke campaign uses `gcd` for training, `aes` for validation and `ibex` for the sealed test split on Nangate45. Evidence is written under `openroad_timing_evolution/work/runs/<id>/`.

## Current status

This branch contains the framework, patch, tests, documentation and presentation deck. The local self-tests exercise grammar rejection, C++/Python policy equivalence and metric rejection. A full OpenROAD QoR campaign is intentionally left as a reproducible command because it requires a long Docker build and complete ORFS runs.
