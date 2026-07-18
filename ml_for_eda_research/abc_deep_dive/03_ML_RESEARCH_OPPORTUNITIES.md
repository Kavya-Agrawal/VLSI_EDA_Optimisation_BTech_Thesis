# 03 — Novel ML Research Opportunities in ABC

> Goal: identify ML applications that are **not already done**. Section 1 maps the
> crowded areas (so you can cite them and avoid them); Section 2–3 lists verified
> gaps with concrete project designs, ranked for BTP feasibility.

---

## 1. What already exists (the crowded map)

### 1.1 Recipe-level RL (choosing the *sequence* of commands)
- **DRiLLS** (ASPDAC'20) — A2C over ABC commands, state = network stats vector.
- **ABC-RL** (ICLR'24) — GNN + MCTS + retrieval over past circuits for recipe search.
- **RL4LS** (ASPDAC'23) — SB3-based, FPGA area.
- **OpenABC-D** (2021) — the dataset for recipe-QoR prediction.
- Verdict: ✗ saturated at the "which command next" granularity.

### 1.2 Learned cut ranking/pruning for technology mapping
- **SLAP** (DAC'21) — supervised priority-cut filter.
- **LEAP** (ICCAD'24) — ML cut sampling, −51% cuts, −2% delay.
- **DeepCut** (ASPDAC'26) — hetero-GNN cut-QoR estimator with cut-cut skip edges.
- **GPA** (2026) — multi-view GNN trained on real post-mapping cell delays.
- Verdict: ✗ crowded, but the *ideas* (features, labels-from-real-mapping) transfer
  to the untouched passes below.

### 1.3 SAT solver guidance (standalone)
- NeuroBack (ICLR'24), Graph-Q-SAT (NeurIPS'20), RLAF (ICLR'26), ImitSAT.
- Verdict: ✗ for standalone solving — but ✓ nobody applies this *inside* synthesis
  loops (see §2.3).

### 1.4 QoR prediction / cross-stage proxies
- OpenABC-D models, LOSTIN, GNN area/delay predictors. Mostly *predict*, don't *act*.

---

## 2. Verified gaps — ranked research directions

Legend: ★ = recommended for BTP (novelty × feasibility × compute budget).

### ★★★ 2.1 Learned resubstitution: divisor & support selection
**Gap check:** Berkeley's own latest resub papers (ISCAS'24 "Enhanced
Resubstitution", IWLS'24 "Information Graph-Based Resubstitution") use unateness
filters and a *greedy/softmax edge-cover* — the ISCAS'24 paper literally
parameterizes divisor choice as `p(xi) ∝ e^(−βH)` and then takes β→∞ (greedy).
Nobody has learned this distribution.

**Project:** replace the divisor-ranking inside `abcResub.c` (or the `res/`
window engine) with a small learned scorer.
- **State/features:** divisor simulation signatures (already computed — free!),
  truth-table entropy, structural distance, level slack, unateness flags.
- **Model:** tiny MLP or GBDT first (SLAP showed trees work and are fast);
  GNN over the window graph as the "sophisticated" upgrade.
- **Label source:** run exhaustive resub offline on small windows → which divisor
  subsets succeeded = supervision. No RL needed to start.
- **Metric:** node reduction at equal runtime / runtime at equal reduction vs
  `resyn2rs` baseline.
- **Novelty claim:** first learned divisor policy for Boolean resubstitution.

### ★★★ 2.2 Learned windowing for don't-care optimization (mfs)
**Gap check:** no published ML for mfs window selection (searched 2024–25).
`mfs` spends a SAT call (≤5000 conflicts) on *every* node's window; most yield
zero gain.
- **Project:** a cheap classifier ("will this window produce a resub?") gating the
  expensive SAT machinery. Features: window size/shape, divisor count, sim-derived
  observability estimates, node function class.
- Training data is trivially generated: run mfs, log per-window features + outcome.
- **Impact story:** same QoR, large runtime cut (industrially very sellable), or
  reinvest saved budget into deeper windows for better QoR.
- This mirrors what AiDRC did for DRC (predict-then-skip) but for logic don't-cares
  — **unexplored**.

### ★★ 2.3 Learned SAT-effort allocation inside SAT-sweeping (fraig/dch/cec)
**Gap check:** NeuroBack/RLAF guide *one* solver run; synthesis makes *thousands
of micro SAT calls* with fixed conflict budgets (dch 1000, fra 100, cec 100) and a
hard-coded `budget^0.7` retry rule.
- **Project:** contextual bandit that, per equivalence-candidate pair, chooses
  {skip, budget-100, budget-1k, budget-10k} to maximize proven merges per second.
- Features: sim-signature agreement length, class size, node depths, previous
  UNSAT/SAT/timeout history (the code already marks "hard" nodes).
- **Novelty claim:** first learned compute-allocation policy for SAT sweeping.

### ★★ 2.4 Node-level rewrite ordering & orchestration
**Gap check:** DRiLLS et al. choose *which pass* runs on the *whole network*;
the *order nodes are visited* within a pass, and *which* of {rw, rf, rs} to apply
*per node*, is fixed. ABC even ships an experimental `abcOrchestration.c` with an
`Abc_NtkOrchGNN` hook — scaffolding exists, learned policy doesn't.
- **Project:** RL/imitation policy that picks (node, transform) pairs; reward =
  node reduction with level constraint. Start with imitation of "oracle greedy"
  (evaluate all three transforms per node offline, learn to predict the argmax
  — 3-way classification, no RL infrastructure needed).
- Connects directly to your MaskPlace-style actor-critic experience: same
  "action-space design" thinking, different domain.

### ★★ 2.5 Learned balancing (depth vs sharing)
**Gap check:** no ML work on AND-tree decomposition found. Balance's sharing bias
looks back at only 8 candidates (`giaBalAig.c`), a purely myopic rule.
- **Project:** learn the leaf-pairing policy — a small pointer-network or scored
  greedy over (level, hash-hit, criticality) features. Clean, self-contained,
  easy to evaluate (depth/area Pareto vs `&b`).

### ★ 2.6 Adaptive recipe early-termination (light novelty, very easy)
Bandit that watches per-pass gain within `resyn2`-style scripts and decides
skip/stop/continue. Less novel than 2.1–2.5 but a good warm-up publication or
ablation section.

### ★ 2.7 Foundation-model direction (high risk, high ceiling)
Pretrain a GNN encoder on AIGs (contrastive over NPN-equivalent subgraphs, or
masked-node prediction; cf. DeepGate-style circuit representation learning) and
fine-tune it as the backbone for 2.1/2.2/2.4 simultaneously. The novelty is a
**shared circuit encoder powering multiple in-tool decisions** — no one has shown
transfer across *passes* (rewrite ↔ resub ↔ mfs) rather than across circuits.

---

## 3. Recommended BTP structure

**Phase 1 (weeks 1–3):** reproduce DRiLLS or ABC-RL on EPFL benchmarks (baseline +
infrastructure sanity). Build the ABC↔Python bridge from `04_ML_INTEGRATION_GUIDE.md`.

**Phase 2 (weeks 4–10):** pick **2.1 (learned resub)** or **2.2 (learned mfs
windowing)** as the core contribution — both are supervised-first (no fragile RL),
data is free to generate, and novelty is verifiable.

**Phase 3 (weeks 11–14):** evaluation vs `resyn2rs`/`&syn2` on EPFL + OpenABC-D
circuits; report area/delay/runtime Pareto; ablate features; (stretch) map results
through `if -K6` and OpenROAD to show downstream PPA impact — that end-to-end
story is what reviewers of ML-EDA papers now demand.

**Datasets/benchmarks:** EPFL combinational suite, ISCAS'85/89, OpenABC-D IPs,
IWLS'05. All load into ABC directly.

**Why these will be defensible as "new":** each attacks a decision that the 2024–26
literature (including Berkeley's own IWLS/ISCAS papers) still implements with
hand-crafted greedy rules, and none of the surveyed ML-EDA work (DRiLLS, ABC-RL,
SLAP, LEAP, DeepCut, GPA, NeuroBack, RLAF, AiDRC) touches them.
