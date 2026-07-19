# NP-hard / intractable problems in ABC where heuristics are used

A catalogue of the places inside Berkeley ABC where the "right" answer is
NP-hard (or worse) to compute, so the tool ships a **heuristic** — i.e. exactly
the spots where a learned model that "knows the problem" can move the needle.
Each entry gives the complexity, the ABC code that implements the heuristic, and
the **prior ML art + how open the area still is** (from the research folder +
2024-26 literature review). Openness legend: 🔴 crowded, 🟠 partly explored,
🟢 wide open.

> The chosen target for this branch (**POLYPHONY**) is #3 attacked from an angle
> nobody has taken (diverse generative *choices*), see `DESIGN.md`.

---

## 1. Technology mapping / covering  🔴
- **Complexity:** optimum-cost covering (LUT or standard-cell) is **NP-hard**;
  binding sub-problems (matching, gate sizing, buffering) compound it.
- **ABC heuristic:** cut-based dynamic programming with area-flow / edge-flow
  cost and a fixed lexicographic cut ranking. `src/map/if/ifCut.c`
  (`If_ManSortCompare`), `ifMap.c`, `src/map/amap`, `src/map/mapper`.
- **Prior ML:** SLAP (DAC'21), LEAP (ICCAD'24), DeepCut (ASPDAC'26), GPA (2026)
  — all learn **cut ranking / QoR**. Crowded at the cut level.
- **Still open 🟠:** *global* covering as an RL/value problem; delay-area Pareto
  conditioning; standard-cell Boolean matching (less explored than LUT).

## 2. Boolean matching (library binding)  🟠
- **Complexity:** tautology check at the core is **co-NP-complete**; NPN
  canonicalization is expensive for >6 inputs.
- **ABC heuristic:** BDD/semi-canonical NPN forms + precomputed class tables.
  `src/bool/lucky` (NPN), `src/map/mapper` matching, `rwrUtil.c` (135 practical
  NPN classes).
- **Prior ML:** thin. Some NPN-classification learning.
- **Open 🟢:** a neural NPN/Boolean matcher or match-selector for cell binding.

## 3. Exact / optimal multi-level synthesis of a Boolean function  ★ target
- **Complexity:** finding the **minimum** circuit (size or depth) for a function
  is **NP-hard**; SAT-based exact synthesis is worst-case exponential, usable
  only for tiny functions.
- **ABC heuristic:** (a) a **precomputed database of optimal 4-input subgraphs**
  used by `rewrite` (`src/opt/rwr`), (b) SAT-based exact synthesis limited to
  small functions: commands `exact`, `twoexact`, `lutexact`, `majexact`
  (`src/base/abci/abc.c` ~L170-181, registered ~L1022-1030), (c) `resub_core`.
- **Prior ML 🔴 for single-circuit generation:** Circuit Transformer (ICLR'24) &
  ctrw (2024), ShortCircuit (AlphaZero, 2024, +18.6% vs ABC on 8-input TTs),
  TGSyn (transformer topo-order for exact synthesis).
- **Still open 🟢 (POLYPHONY's niche):** generating a **diverse set of
  equivalent** implementations (not one minimal circuit) to feed **choice-based
  mapping** — no prior work targets diversity/choices.

## 4. BDD variable ordering  🟢
- **Complexity:** optimal ordering is **NP-complete** (co-NP-complete to verify);
  BDD size varies exponentially with order.
- **ABC heuristic:** CUDD **sifting** (greedy). `src/bdd/cudd/cuddReorder.c`;
  used by `collapse`, `bdd`, `dsd`, don't-care computation.
- **Prior ML 🟠:** a few RL/GNN ordering papers, none integrated in ABC.
- **Open 🟢:** GNN one-shot order prediction + RL swap fine-tuning, in-tool.

## 5. SAT solving (used everywhere: fraig, dch, mfs, cec, pdr)  🔴
- **Complexity:** **NP-complete**; branching/variable ordering decide runtime.
- **ABC heuristic:** VSIDS, Luby restarts, fixed conflict budgets.
  `src/sat/bsat/satSolver.c`.
- **Prior ML 🔴:** NeuroBack (ICLR'24), Graph-Q-SAT, RLAF (ICLR'26).
- **Open 🟠:** *compute-budget allocation* across the millions of tiny in-synthesis
  SAT calls (not the solver itself) — untouched.

## 6. Don't-care based optimization (mfs)  🟢
- **Complexity:** windowed resub with observability don't-cares; SAT-hard per node.
- **ABC heuristic:** fixed window (TFO=2, cap 300), SAT budget 5000, applied to
  *every* node. `src/opt/mfs`.
- **Open 🟢:** learned "will this window pay off?" gate (predict-then-skip).

## 7. Retiming (sequential)  🟠
- **Complexity:** min-period retiming is polynomial, but **min-area retiming
  under a period constraint** and retiming+resynthesis are **NP-hard**.
- **ABC heuristic:** `src/opt/ret`, `src/opt/fret`.
- **Open 🟢:** RL for combined retiming+resynthesis move selection.

## 8. Algebraic factoring / fast extract (kernel/co-kernel, rectangle covering) 🟢
- **Complexity:** optimal common-divisor extraction = **NP-hard rectangle
  covering**.
- **ABC heuristic:** greedy value-based rectangle covering. `src/opt/fxu`,
  `src/opt/fxch` (`fx`).
- **Open 🟢:** RL/GNN divisor (rectangle) selection — almost no ML work.

## 9. Logic rewriting: subgraph & cut selection  🟠
- **Complexity:** choosing the best replacement over enumerated cuts + NPN
  subgraphs is combinatorial.
- **ABC heuristic:** greedy max-gain, 4-input cuts, ≤250 cuts. `src/opt/rwr/rwrEva.c`.
- **Prior ML 🟠:** SYNAPSE (this repo, other branch) reranks resub divisors;
  DeepCut touches rewrite QoR.
- **Open 🟢:** node-visit ordering; subgraph choice for k>4.

## 10. Disjoint-support decomposition (DSD) / bi-decomposition  🟢
- **Complexity:** general Boolean decomposition is hard.
- **ABC heuristic:** `src/bool/bdc`, `src/aig/gia` DSD, `src/opt/dsc`.
- **Open 🟢:** learned decomposition-point selection.

## 11. FSM state encoding / assignment  🟢
- **Complexity:** optimal encoding is **NP-hard**.
- **ABC heuristic:** classic heuristics in `src/base/ver`/io + external.
- **Open 🟢:** rarely touched by modern ML.

## 12. Logic clustering / partitioning (for windowing, parallelism)  🟠
- **Complexity:** balanced graph partitioning is **NP-hard**.
- **ABC heuristic:** cone/window heuristics across passes.
- **Prior ML 🟠:** GNN partitioning exists generally, not in ABC.

## 13. Phase / polarity assignment  🟢
- **Complexity:** global inverter/phase minimization is **NP-hard**.
- **ABC heuristic:** local rules during balancing/mapping.

## 14. Cut enumeration limits / priority cuts  🔴
- **Complexity:** exponential cut space; must prune.
- **ABC heuristic:** keep ≤ nCutsMax cuts by a fixed cost. `src/map/if/ifCut.c`.
- **Prior ML 🔴:** SLAP/LEAP/DeepCut (same as #1).

---

## How the research-folder papers inform the approach
- **RethinkingRL (2022):** warns that RL synthesis agents often become
  *state-agnostic* (ignore the circuit). → POLYPHONY's generator is **conditioned
  on the exact truth table** and its outputs are **verified equivalent**, so it is
  function-aware *by construction* and cannot silently degenerate.
- **LogicSynthesisMeetsML / IWLS'20:** "the circuit *is* the model"; exactness ↔
  generalization. → We keep **exactness** (verify every generated circuit) but
  borrow the generative/learning view to explore the space of implementations.
- **DRiLLS / ABC-RL:** recipe-level RL (crowded). → We go *below* the recipe, to
  structural generation, where learning still has headroom.
- **Circuit Transformer / ShortCircuit (2024):** generative single-circuit
  synthesis works and beats ABC on small TTs. → We reuse the feasibility insight
  but change the **objective to diversity** and the **use to choice injection**.

## Openness summary (best targets for a BTP, ranked)
1. 🟢 **#3 diverse generative choices** (POLYPHONY — this branch)
2. 🟢 **#6 mfs pay-off gating** (light, high runtime win)
3. 🟢 **#4 BDD ordering** (clean NP-complete RL)
4. 🟢 **#8 factoring/rectangle covering** (almost no ML)
5. 🟠 **#1/#14 global covering value net** (differentiate from cut-ranking)
