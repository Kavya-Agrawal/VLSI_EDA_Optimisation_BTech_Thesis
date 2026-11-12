# Reading Order: 30-Minute Guide to PV-Resizer-Evolve

This guide is for a new researcher or engineer who wants to understand this repository in 30 minutes.

---

### Step 1: The High-Level Vision & Framework Overview (5 mins)
1. **[README.md](file:///Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/README.md)**
   - Start here. Learn the premise of the branch `pv_resizer_evolve`: autonomous multi-agent evolution of OpenROAD's Post-Placement Timing Optimization (`src/rsz`) engine.
2. **[00_docs/PLAN.md](file:///Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/00_docs/PLAN.md)**
   - Read the architectural blueprint and operational roadmap, detailing Phase 1 (profiling & context extraction) and Phase 2 (the multi-agent LLM evolution loop).

---

### Step 2: System Architecture & Hardware-Agent Contracts (7 mins)
3. **[00_docs/architecture.md](file:///Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/00_docs/architecture.md)**
   - Understand the component layout: frozen baseline snapshot (`01_openroad_original`), active evolved champions (`02_openroad_evolved`), benchmark suites (`04_benchmarks`), and the agent orchestration layer (`03_evolution_framework`).
4. **[09_agent_context/EVAL_CONTRACT.md](file:///Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/09_agent_context/EVAL_CONTRACT.md)**
   - See how code mutations are judged: fast pre-route OpenSTA timing extraction over placed DEF/LEF, WNS/TNS paired scoring against the champion, and strict fail-closed constraints (equivalence, legal placement, zero DRC regressions).

---

### Step 3: Resizer Deep Dive & Algorithmic Context (10 mins)
5. **[09_agent_context/00_BIG_PICTURE.md](file:///Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/09_agent_context/00_BIG_PICTURE.md)**
   - The master engineering handbook of `src/rsz`: the STA incremental timing loop, exact command dispatch map from `Resizer.tcl`, and end-to-end pseudo-code of setup timing repair.
6. **Pick one Algorithm Dossier** under `09_agent_context/algorithms/`:
   - E.g., **[setup_strategy.md](file:///Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/09_agent_context/algorithms/setup_strategy.md)** to see how critical path target collection and optimization policies interact.
   - Or **[buffering.md](file:///Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/09_agent_context/algorithms/buffering.md)** to understand Steiner tree construction, van Ginneken-style tree rebuffering, and inverter pair decomposition.

---

### Step 4: Baselines & Results (5 mins)
7. **[05_baseline_results/SUMMARY.md](file:///Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/05_baseline_results/SUMMARY.md)**
   - Review the stock OpenROAD resizer baseline metrics (WNS, TNS, area, runtime) across the benchmark tiers.
8. **[07_visualizations/index.html](file:///Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/07_visualizations/index.html)**
   - Open this web report in your browser to view interactive charts of generation scores, WNS/TNS progression curves, and path slack distributions.

---

### Step 5: Literature & Theory (3 mins)
9. **[00_docs/literature_notes.md](file:///Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/00_docs/literature_notes.md)**
   - Read the survey linking EDA classical literature (Lagrangian relaxation, TILOS, van Ginneken, slack budgeting) to modern LLM-driven EDA evolution (DAC '26 Self-Evolved ABC, SATLUTION, AlphaEvolve).
