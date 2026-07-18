# 02 — The Heuristic Map: every ML injection point in ABC

> Every optimization pass in ABC is a greedy local search with hand-tuned
> constants. This document catalogs **where those decisions are made**, what the
> current rule is, and **what features an ML model could consume at that point**.
> Paths relative to `hardware_eda/abc/src`.

---

## 1. Rewriting (`rewrite`, `drw`/dc2)

**Files:** `base/abci/abcRewrite.c` (driver), `opt/rwr/rwrEva.c` (`Rwr_NodeRewrite`,
`Rwr_CutEvaluate`), `opt/rwr/rwrMan.c`/`rwrUtil.c` (NPN tables), DAR twin:
`opt/dar/darCore.c`.

**Algorithm:** for each node → enumerate 4-input cuts (keep ≤250) → canonize the
16-bit truth table to one of **135 practical NPN classes** → try each precomputed
replacement subgraph of that class → gain = (MFFC nodes freed) − (new nodes added,
counting reuse of existing hashed logic) → **greedily accept if gain > 0**.

| Decision | Current rule | Features available |
|---|---|---|
| Skip node? | fanout > 1000 | fanout, level, MFFC size, refs |
| Which cut? | try all 4-leaf cuts, take max gain | cut truth/NPN class, leaf levels/fanouts, required time |
| Which subgraph in class? | max `nodesSaved − nodesAdded` | subgraph shape/depth, reuse hits in hash table |
| Accept? | gain > 0 (or =0 with `-z`) | gain, level delta |
| **Node visit order** | fixed topological | whole-graph state — *ordering is unstudied* |

**Knobs:** cut size 4; 250 cuts kept; fanout skip 1000; DAR: `nCutsMax=8`,
`nSubgMax=5` (a literal "magic number" in `darCore.c`).

---

## 2. Refactoring (`refactor`) & Resubstitution (`resub`)

**Refactor** (`base/abci/abcRefactor.c` + `abcReconv.c`): pull a reconvergence-
driven cone (≤10 node / ≤16 leaf), collapse to truth table, re-factor via ISOP,
accept if it saves nodes. Decisions: *which cone*, accept threshold.

**Resub** (`base/abci/abcResub.c`): for each node, collect ≤150 divisors (pairs
≤500), simulate, then try resubs **in a fixed order** (constant → 0-node → 1-node
→ 2-node → 3-node) — **first success wins**, not best-of.

| Decision | Current rule | Features |
|---|---|---|
| Divisor set | structural proximity + caps (150/500) | divisor sim signatures, unateness, level, distance |
| Support choice | unateness heuristics, greedy edge-cover (see Berkeley ISCAS'24: softmax β→∞ = greedy) | truth tables, care set |
| Which resub to try first | fixed 0→1→2→3 order | node function, divisor pool stats |
| Window (res/ package) | `nWindow` = TFI*10+TFO, fanout limit 10 | window topology |

This is a **verified open area**: Berkeley's own 2024–25 papers still use
hand-crafted divisor-selection heuristics (see `03_ML_RESEARCH_OPPORTUNITIES.md` §3.1).

---

## 3. Balancing (`balance`, `&b`)

**Files:** `base/abci/abcBalance.c`; GIA: `aig/gia/giaBalAig.c`.

Collects multi-input AND "supergates" (cap 10000 leaves), sorts leaves by level
descending, pairs the two lowest-level leaves — with a **sharing bias**: prefer a
partner whose AND already exists in the hash table (GIA looks back only at the
**last ≤8 candidates**, `giaBalAig.c:243`).

**ML angle:** tree decomposition = sequence of pairing decisions; the sharing/depth
trade-off is decided by a myopic rule. Features: leaf levels, polarities,
hash-hit indicators, criticality.

---

## 4. Priority-cut mapping (`if`, `&if` — FPGA LUTs)

**Files:** `map/if/ifCore.c` (defaults + pass schedule), `ifMap.c` (DP per node),
`ifCut.c` (ranking).

**Algorithm:** per node keep ≤`nCutsMax=8` cuts, ranked by a **lexicographic cost**
(`If_ManSortCompare`): delay-mode = Delay→#leaves→Area→Edge→Power; area-mode =
Area→Edge→Power→#leaves. Best cut = `ppCuts[0]`. Mapping = several rounds:
delay → area-flow → exact-area recovery (`ifCore.c:123–164`).

| Decision | Current rule | Features |
|---|---|---|
| Cut ranking | fixed lexicographic order | Delay, Area/Edge/Power flows, nLeaves, EstRefs, truth/DSD |
| Cut set pruning | dominance + keep 8 | same |
| Pass schedule | fixed (1 flow + 2 area iters) | global stats per round |

**Note:** this is the *most crowded* ML area (SLAP/LEAP/DeepCut/GPA all attack cut
ranking or pruning) — good to learn from, bad for novelty. Standard-cell analogs:
`map/mapper/mapperMatch.c` (`Map_MatchCompare`), `map/amap/` (`nCutsMax=500`).

---

## 5. SAT-sweeping & choices (`fraig`, `dch`, `&fraig`, cec)

**Files:** `proof/dch/dchCore.c` (choices), `proof/fra/fraMan.c` (fraig),
`proof/cec/cecCore.c` (CEC).

**Algorithm:** random simulation partitions nodes into candidate-equivalence
classes → SAT proves/refutes pairs under a **conflict budget** → merge/choice.

| Decision | Current rule | Features |
|---|---|---|
| Which pairs to SAT-check first | class order from sim | class size, sim-signature entropy, node depth, past SAT hardness |
| Conflict budget per call | fixed: dch 1000, fra 100/node, cec 100 | node/pair features, budget spent so far |
| Hard-node handling | budget^0.7 retry (`fraSat.c:68`) | SAT stats history |
| Sim effort | fixed words/rounds (dch 8 words; cec 31 words, 20 rounds) | class refinement rate |

**Knobs:** `nBTLimit=1000`, `nSatVarMax=5000`, `nCallsRecycle=100` (dch);
`dSimSatur=0.005`, `MaxScore=25`, cone-activity bump 0.3 (fra).

---

## 6. Don't-care optimization (`mfs`)

**Files:** `opt/mfs/mfsCore.c`, `mfsWin.c`, `mfsResub.c`.

Per node: build a window (TFO levels=2, fanout cap 30, depth cap 20, size cap
300) → compute care set via SAT (≤5000 conflicts) → resub with don't-cares.

**Decisions:** *which nodes are worth windowing at all* (today: all of them),
window shape, divisor cap, SAT budget. Runtime is dominated by windows that yield
nothing — a learned "will this window pay off?" filter is an obvious win and
**no published work does it** (verified).

---

## 7. SAT solver internals (`sat/bsat/satSolver.c`)

Fixed heuristics: VSIDS decay 0.95, random branch 2%, Luby×100 restarts,
learnt-clause keep ratio. Callers (dch/fra/mfs/cec) pass fixed conflict limits.
Existing ML literature (NeuroBack, RLAF) targets standalone SAT — **budget
allocation across thousands of tiny EC calls inside synthesis is untouched**.

---

## 8. Sequence level (the recipes themselves)

`resyn2 = "b; rw; rf; b; rw; rwz; b; rfz; rwz; b"` (`abc.rc`). Fixed for all
circuits. DRiLLS/ABC-RL learn better recipes — crowded, but the *bandit/early-stop
within a fixed recipe* variant (skip passes predicted useless) is lighter and less
explored.

---

## 9. Bonus: ABC already has ML scaffolding

- `base/abci/abcOrchestration.c` — experimental per-node **orchestration** of
  rewrite/resub/refactor with hooks named `Abc_NtkOrchGNN` and `Abc_NtkOrchSA`
  (simulated annealing). A learned policy can be wired into the same interface.
- `&mlgen` / `&mltest` commands — dump/test simulation datasets from a GIA.

---

## 10. Master table of hand-tuned constants (cheat sheet)

| Constant | Value | Where |
|---|---|---|
| Rewrite cut size / kept cuts / fanout-skip | 4 / 250 / 1000 | `abcRewrite.c` |
| Practical NPN classes | 135 | `rwrUtil.c` |
| DAR cuts / subgraphs tried | 8 / 5 ("magic") | `darCore.c` |
| Refactor cone / leaves | 10 / 16 | `abc.c` defaults |
| Resub K / divisors / pairs | 8 / 150 / 500 | `abcResub.c` |
| Balance supergate cap / GIA look-back | 10000 / 8 | `abcBalance.c`, `giaBalAig.c` |
| IF cuts kept / flow / area iters / ε | 8 / 1 / 2 / 0.005 | `ifCore.c` |
| AMAP cuts | 500 | `amapCore.c` |
| DCH sim words / conflicts / sat vars | 8 / 1000 / 5000 | `dchCore.c` |
| FRA conflicts node/miter | 100 / 500000 | `fraMan.c` |
| CEC conflicts / sim words / rounds | 100 / 31 / 20 | `cecCore.c` |
| MFS window / fanout / depth / TFO / conflicts | 300 / 30 / 20 / 2 / 5000 | `mfsCore.c` |
| bsat decay / random / restart | 0.95 / 0.02 / Luby×100 | `satSolver.c` |

Every row of this table is, in effect, a **frozen decision an ML model could make
adaptively** — per node, per window, per circuit, or per budget.
