# pv_resizer_evolve — Autonomous Evolution of OpenROAD's Timing Resizer (`rsz`)

B.Tech Project (BTP) — Indian Institute of Technology Guwahati (IITG)  
**Student:** Kavya Kumar Agrawal  
**Branch:** `pv_resizer_evolve`

---

## Executive Summary

`pv_resizer_evolve` is an autonomous multi-agent framework designed to **evolve the algorithms and heuristics inside OpenROAD's physical synthesis and timing repair engine (`rsz`)**. Unlike prior automated EDA evolution systems in logic synthesis (e.g., Self-Evolved ABC) that rely exclusively on Combinational Equivalence Checking (CEC) as a functional oracle, evolving physical design tools requires satisfying a **Physical Verification Correctness Contract (PVCC)** across compilation, placement legality, electrical design rules, dual setup-hold timing constraints, and numerical determinism.

The framework combines:
1. **Graphify Knowledge Graphs:** Structural navigation of OpenROAD's C++ codebase and Resizer dependency clusters.
2. **Timing-Path-Guided Mutation (TPGM):** Clustered search guided by the top failing OpenSTA paths, feature attribution matrices ($w_i$), and physical slack sensitivities.
3. **Fail-Closed PVCC Safety Engine:** Immediate rejection of illegal placements, electrical violations (max slew/cap), and hold regressions before downstream scoring.
4. **Multi-Agent Orchestration:** Hierarchical loop with Planner, cluster-scoped C++ Coders, and automated Evaluator agents.

---

## Quick Start: Interactive Inspection & Demonstration Suite

To inspect real execution traces, 3,500 candidate evaluation records, OpenSTA critical paths, and authentic C++ diffs directly in the terminal, run the following `make` commands:

```bash
# 1. Stream all 3,500 candidate evaluation records & QoR percentile analytics
make show-sweep

# 2. View all 20 OpenSTA critical paths & TPGM feature attribution matrix
make show-tpgm

# 2b. View verbose Feature-to-Code Sensitivity Matrix M_{i, j} with mathematical breakdown
make show-matrix

# 3. View the complete, untruncated 35-stage OpenSTA timing path for Ibex (fanout 943)
make show-bottleneck

# 4. View authentic unified git diffs of the evolved OpenROAD Resizer move engine
make show-diff

# 5. View stock OpenROAD baseline metrics across Nangate45 benchmarks
make show-baseline

# 6. View the formal 6-layer PVCC correctness contract and verification gates
make show-contract

# 7. Open the interactive command menu
make demo
```

---

## Detailed Command Reference & Inspection Tools

All commands are powered by the native CLI tool [`demo_cli.py`](demo_cli.py) and query real datasets, AST snapshots, and benchmark reports on disk.

### 1. `make show-sweep` — 3,500 Candidate Evaluation Sweep Ledger
Streams **all 3,500 candidate evaluation records** from `11_agent_data/candidates_sweep/candidates.csv` without truncation or ellipses, followed by the comprehensive statistical distribution ledger from `analysis.json`.

```bash
# Stream all 3,500 records + summary statistics
make show-sweep

# Filter only accepted candidates (passed all 6 PVCC layers with positive gain)
./demo_cli.py sweep --filter accepted

# Filter only top-tier champion candidates (score >= 1.5)
./demo_cli.py sweep --filter champion

# Filter only rejected candidates (failed build, placement legality, or timing)
./demo_cli.py sweep --filter rejected

# Inspect the first N or last N candidates
./demo_cli.py sweep --limit 50
./demo_cli.py sweep --tail 50

# View only the percentile distribution analytics and histogram
./demo_cli.py sweep --stats
```

**Output Columns:**
* `Iter`: Candidate evaluation index (1 to 3,500).
* `Candidate Hash`: Unique 12-character SHA identifier.
* `Mutated Parameters`: Target policy parameters (load weight, density weight, late weight, etc.).
* `+/-`: Lines added and removed in the patch.
* `ΔWNS (%)` / `ΔTNS (%)`: Measured percentage change in setup timing slacks.
* `ΔTime`: Incremental wall-clock runtime delta.
* `Score`: Composite multi-metric objective score.
* `PVCC Contract`: Verification status (`L1-L6 PASS`, `L1 FAIL`, `L3 FAIL (LEGAL)`, `L5 FAIL (HOLD)`).
* `Status`: Final decision (`ACCEPTED`, `REJECTED`, or `CHAMPION`).

---

### 2. `make show-tpgm` — Timing-Path-Guided Mutation & Attribution Matrix
Displays the **top 20 critical timing paths** extracted via OpenSTA on Nangate45 GCD without omitting any paths, followed by the mathematical feature attribution matrix mapping timing violations directly to Resizer code blocks:

```bash
make show-tpgm
```

**What it displays:**
1. **Full 20/20 Path Ledger:** Endpoint pin (`_362_/D` to `_354_/D`), slack (ns), arrival time, logic depth, max fanout, total load capacitance (pF), pin count, and attributed features (`load`, `fanout`, `position_late`).
2. **Mathematical Attribution Formula:**
   $$w_i = \sum_{p=1}^{20} \max(0, -\text{slack}(p)) \times \frac{|\text{reads}(b_i) \cap \text{features}(p)|}{|\text{reads}(b_i)|}$$
3. **Code Block Sensitivity Weights:**
   * `late_path_focus`: 31.2% (dominant: deep paths with late arrival)
   * `load_pressure`: 26.8% (dominant: high wire/pin capacitance)
   * `fanout_shock`: 22.4% (dominant: high fanout driver slew degradation)
   * `stability_damper`: 19.6% (dominant: anti-thrashing quadratic damper)
4. **Synthesized C++ AST Mutation:** The exact C++ patch generated for `SetupLegacyBase.cc`.
5. **Post-Repair Timing Verification:** Verifies WNS recovery from -0.042 ns to -0.018 ns (+57.1% path recovery).

---

### 3. `make show-bottleneck` — Complete 35-Stage Ibex Path & Fanout-943 Barrier
Dumps the complete, untruncated **35-stage OpenSTA critical path report** for the Ibex RISC-V core from `06_evolved_results/0002_setup_strategy/paths_attribution.json`:

```bash
make show-bottleneck
```

**Physical Findings Highlighted:**
* **Stage 34:** Pin `_26153_/ZN` (`AND2_X1`) driving a net with **fanout = 943 sinks**, transition slew = 2.088 ns, and stage delay increment = 1.2788 ns.
* **OpenROAD Warning:** `[WARNING RSZ-0062] Net driven by _26153_/ZN has fanout 943 > kRebufferMaxFanout (20)`.
* **Root Cause in Source Code:** `src/rsz/src/BufferTree.cc` line 142 hardcodes `constexpr int kRebufferMaxFanout = 20;` which aborts buffering on large nets.
* **Device Physics:** Driver on-resistance $R_{\text{on}} \approx 9.4\text{ k}\Omega$, load capacitance $C_{\text{load}} \approx 1.63\text{ pF}$, giving an intrinsic RC time constant $\tau \approx 15.3\text{ ns} \gg T_{\text{clk}} = 1.76\text{ ns}$.

---

### 4. `make show-diff` — Unified C++ Git Diffs of Evolved Resizer
Displays authentic unified git diffs between original OpenROAD baseline snapshots and evolved candidate implementations:

```bash
# View the primary SizeUpGenerator.cc move ranking diff (354 lines of C++)
make show-diff

# View specific diff targets
./demo_cli.py diff --file generator  # src/rsz/src/move/SizeUpGenerator.cc
./demo_cli.py diff --file header     # src/rsz/src/move/SizeUpGenerator.hh
./demo_cli.py diff --file candidate  # src/rsz/src/move/SizeUpCandidate.hh
./demo_cli.py diff --file policy     # src/rsz/src/policy/SetupLegacyBase.cc
```

---

### 5. `make show-baseline` & `make show-contract`
* `make show-baseline`: Outputs stock OpenROAD baseline measurements across Nangate45 GCD, AES, and Ibex (WNS, TNS, Area, Buffers, Runtime).
* `make show-contract`: Outlines the formal 6-layer PVCC specification with fail-closed safety invariants ($L_1$ to $L_6$).

---

## Repository Map

| Directory | Contents & Function |
|---|---|
| [`00_docs/`](00_docs/) | Architectural plans, reproduction runbooks, and design logs. |
| [`01_openroad_original/`](01_openroad_original/) | Frozen read-only snapshot of stock OpenROAD `src/rsz` and OpenSTA headers. |
| [`02_openroad_evolved/`](02_openroad_evolved/) | Evolved candidates, champion source trees, candidate patches, and `lineage.json`. |
| [`03_evolution_framework/`](03_evolution_framework/) | The `rszevolve` Python package: orchestrator, prompt builders, evaluators, and Tcl drivers. |
| [`04_benchmarks/`](04_benchmarks/) | Placed circuit checkpoints and SDC constraints per design tier. |
| [`05_baseline_results/`](05_baseline_results/) | Baseline WNS/TNS/Area numbers for stock OpenROAD (3 replicates). |
| [`06_evolved_results/`](06_evolved_results/) | Per-iteration evaluation metrics, path reports, attribution files, and feedback dossiers. |
| [`07_visualizations/`](07_visualizations/) | Visual analytics, QoR convergence plots, and HTML dashboards. |
| [`08_graphify/`](08_graphify/) | Graphify knowledge graphs covering OpenROAD and the Resizer dependency network. |
| [`09_agent_context/`](09_agent_context/) | Context packs for sub-agents: per-file cards, AST guides, and algorithm dossiers. |
| [`10_agent_knowledge/`](10_agent_knowledge/) | Cumulative learning ledger: rules, failure modes, hypothesis tracking, and dead ends. |
| [`11_agent_data/`](11_agent_data/) | Full 3,500 sweep ledger (`candidates.csv`), raw agent prompts, and token logs. |
| [`tools/`](tools/) | Environment verification, dependency installers, Docker container files, and build wrappers. |

---

## The 6-Layer Physical Verification Correctness Contract (PVCC)

In physical design, candidate patches cannot be accepted on functional equivalence alone. Every candidate $c$ must pass six sequential, fail-closed verification layers against champion $r$:

$$\mathcal{C}(c, r) = \bigwedge_{k=1}^6 L_k(c, r)$$

1. **$L_1$ (Compilation & Link Safety):** Clang-14 and Bazel incremental build check. Any syntax, typing, or symbol error terminates immediately.
2. **$L_2$ (Unit Test Invariants):** 100% pass on 6 Resizer unit test suites (pre-checks, skew budgeting, nested journals).
3. **$L_3$ (Physical Placement Legality):** OpenDP overlap and boundary audit:
   $$\text{IllegalOverlaps}(c) = 0 \quad \wedge \quad \text{RowBoundaryViolations}(c) = 0$$
4. **$L_4$ (Electrical DRC Invariant):** Max slew and max pin capacitance violations must be zero or non-worsening:
   $$\text{SlewViolations}(c) \le \text{SlewViolations}(r) \quad \wedge \quad \text{CapViolations}(c) \le \text{CapViolations}(r)$$
5. **$L_5$ (Hold Slack Monotonicity):** Zero hold-time degradation ($\tau_{\text{hold}} = 0.00\text{ ns}$):
   $$\Delta\text{HoldWNS}(c, r) \ge -\tau_{\text{hold}}$$
6. **$L_6$ (Multi-Replicate Determinism):** Two independent evaluation passes must yield identical timing results ($\Delta\text{WNS} < 10^{-5}\text{ ns}$).

---

## Plan for Next Semester (BTP Phase-II Roadmap)

Phase-I successfully proved the feasibility of autonomous physical design evolution, quantified the 3,500-patch empirical distribution, formulated the PVCC contract, built the TPGM attribution pipeline, and pinpointed the Ibex 943-fanout bottleneck.

In Phase-II, work will focus on the following four concrete milestones:

```
  +-----------------------------------------------------------------------------------+
  |                               BTP PHASE-II ROADMAP                                |
  +-----------------------------------------------------------------------------------+
           |
           +---> [Milestone 1: Scaled Autonomous Evolution Runs]
           |     - Execute campaigns of N >= 50 iterations per run
           |     - Formal champion lineage tracking with automated rollback
           |     - Resilient multi-LLM provider fallback (Claude -> o1 -> Gemini)
           |
           +---> [Milestone 2: High-Fanout Timing Move & Ibex Resolution]
           |     - Remove the fanout <= 20 guard in BufferTree.cc line 142
           |     - Develop hierarchical balanced H-tree buffer generator for FO >= 50
           |     - Close timing on the 35-stage Ibex critical path (tau: 15.3ns -> <1.5ns)
           |
           +---> [Milestone 3: Benchmark & Node Expansion (Generalization)]
           |     - Evaluate beyond Nangate45 (45nm) on ASAP7 (7nm) and SKY130 (130nm)
           |     - Test on complex SoC cores: SWERV, Ariane 64-bit, AES, Ethernet MAC
           |     - Validate cross-PDK physical scaling invariance
           |
           +---> [Milestone 4: OptMirror-Resizer Co-Evolution & Open-Source Release]
                 - Link detailed-placement OptMirror with Resizer timing feedback loops
                 - Upstream evolved C++ patches to the official OpenROAD project
                 - Prepare and submit conference paper to IEEE/ACM DAC / ICCAD
```

### Milestone 1: Scaled Autonomous Evolution Runs
* **Objective:** Move from short test bursts to multi-day autonomous evolution campaigns ($N \ge 50$ iterations per campaign).
* **Deliverables:**
  * Fully automated checkpointing and crash recovery across restarts.
  * Adaptive token budget allocation and dynamic model routing (using Claude 3.5 Sonnet for AST synthesis, OpenAI o1 for hypothesis planning, and Gemini 1.5 Pro for large-context log analysis).
  * Formal champion convergence verification across Nangate45 GCD, AES, and Ibex.

### Milestone 2: Timing-Aware High-Fanout Move & Ibex Bottleneck Resolution
* **Objective:** Resolve the primary physical bottleneck uncovered in Phase-I—the fanout-943 `AND2_X1` net in Ibex where standard buffering aborts.
* **Deliverables:**
  * Implement an agent-evolved hierarchical buffer tree generator in `src/rsz/src/BufferTree.cc` specifically triggered for nets with $\text{fanout} \ge 50$.
  * Replace flat buffering with a 3-level balanced tree synthesis algorithm that splits capacitive load while respecting OpenDP placement legality.
  * Target setup timing closure on Ibex: reducing arrival delay from 1.892 ns to under 1.592 ns ($\text{WNS} \to 0.00\text{ ns}$).

### Milestone 3: Benchmark & Technology Node Expansion
* **Objective:** Prove that evolved algorithmic heuristics represent genuine physical improvements rather than PDK-specific overfitting.
* **Deliverables:**
  * Port benchmark checkpoints to **ASAP7 (7nm FinFET)** and **SkyWater SKY130 (130nm planar)**.
  * Incorporate larger industrial designs from OpenROAD-flow-scripts: SWERV RISC-V core, Ariane (CVA6) 64-bit application core, and dynamic JPEG/DSP blocks.
  * Verify stability of TPGM feature attribution across distinct library non-linear lookup tables (NLDM / CCS).

### Milestone 4: Selective OptMirror–Resizer Co-Evolution & OpenROAD Contribution
* **Objective:** Connect placement-level optimization with post-placement timing repair and package results for academic dissemination.
* **Deliverables:**
  * Revisit Phase-I's `OptMirror` cell-mirroring framework: couple cell orientation swapping with downstream timing criticality feedback from OpenSTA.
  * Package the entire autonomous evolution suite, PVCC verification harness, and evolved C++ resizer patches as a documented open-source contribution to the upstream OpenROAD GitHub repository.
  * Author a full research paper targeting submission to top-tier IEEE/ACM EDA conferences (**DAC / ICCAD / DATE**).

---

## Reproduction & Development Guide

```bash
# Verify system dependencies, compilers, and RAM/disk
make env-check

# Install OS dependencies (macOS via brew, Linux via apt)
make deps

# Clone pinned OpenROAD and ORFS repositories
make setup

# Compile stock OpenROAD binary with Bazel and freeze snapshot
make build-openroad snapshot

# Generate Graphify knowledge graphs and agent context dossiers
make graphify context

# Run ORFS to generate placed circuit checkpoints
make checkpoints baseline

# Launch autonomous multi-agent evolution loop (N iterations, budget cap)
make evolve N=5 BUDGET_USD=20 TIER=A

# Inspect champion progress and generated reports
make report viz show-champion
```

---

## Status & Lockfiles

All tools, dependencies, and git submodules are pinned in [`VERSIONS.lock`](VERSIONS.lock) for reproducible builds. Current evolution state and candidate lineages can be checked at any time via:
```bash
make status
```
