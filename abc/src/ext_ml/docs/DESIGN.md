# SYNAPSE — Synthesis-Aware Neural-Aided Policy for Search & Efficiency

*A circuit-foundation-model-driven optimization co-processor embedded natively inside Berkeley ABC.*

Status: research prototype (architecture + hooks complete; training requires GPU, not yet run).
Branch: `feature/synapse-ml-abc`. Module: `abc/src/ext_ml`.

---

## 1. The core thesis (why this can "work miracles")

Every technology-independent optimization in ABC — `rewrite`, `refactor`,
`resub`, `balance`, `mfs` — is, under the hood, a **greedy local search** that
commits a transformation whenever it reduces the node count *at that instant*.
Three structural weaknesses follow from this, and SYNAPSE attacks all three with a
single shared neural substrate:

### Weakness 1 — Myopia (the big one)
ABC's acceptance rule is `gain = MFFC_nodes_freed - nodes_added > 0`. This is a
**one-step-greedy** objective. But logic synthesis is a *sequence* (`resyn2` =
10 passes); a transformation that looks neutral or slightly bad now can unlock a
large reduction three passes later (e.g. it exposes a shared cut, or creates a
reconvergence that `mfs` later exploits). The greedy metric cannot see this.

> **SYNAPSE contribution:** a *non-myopic value head* `V(node, action)` trained to
> predict the **eventual contribution to final QoR after the entire recipe**, not
> the immediate gain. This is credit assignment across the synthesis flow — the
> same idea that made value functions transformative in RL, applied for the first
> time at the *node-transform* granularity inside a production synthesis tool.

### Weakness 2 — Fixed, hand-tuned candidate ordering
`resub` tries divisors in a frozen order (const → 1-node → 2-node → 3-node) and
takes the *first* success, not the best. `if` ranks cuts by a fixed lexicographic
cost. `mfs` builds a SAT window for *every* node even though most yield nothing.

> **SYNAPSE contribution:** a *ranking head* that reorders candidates (divisors,
> cuts, windows) by predicted payoff so the good ones are tried first — while
> ABC's existing exact checks (truth tables / SAT) still guarantee correctness.
> Nothing can become *wrong*, only faster and/or better.

### Weakness 3 — No cross-pass knowledge transfer
Prior ML-for-ABC work (SLAP, LEAP, DeepCut, DRiLLS) trains a **separate** model
for **one** decision. Knowledge learned about circuit structure for cut-ranking is
thrown away and re-learned for resub.

> **SYNAPSE contribution:** one **pretrained AIG foundation encoder** produces node
> embeddings consumed by *all* task heads. Structure understanding is learned once
> (self-supervised) and transfers across rewrite/resub/mfs/mapping. This is a
> circuit foundation model *deployed in-tool*, which the 2026 "Autonomous Evolution
> of ABC" paper explicitly identified as the missing piece (external ML frameworks
> don't integrate with the C codebase).

---

## 2. System architecture

```
                          ┌──────────────────────────────────────────────┐
                          │                 ABC process                    │
                          │                                                 │
   AIG / GIA  ───────────▶│  ext_ml feature extractor (mlFeatures.c)        │
   (Gia_Man_t)            │      per-node structural+functional vectors     │
                          │      + edge_index (for GNN message passing)     │
                          │                    │                            │
                          │                    ▼                            │
                          │  inference layer (mlInfer.c)                    │
                          │   ┌───────────────────────────────────────┐    │
                          │   │  #ifdef ABC_USE_ONNX                   │    │
                          │   │     ONNX Runtime C API  ◀── synapse.onnx│   │
                          │   │  #else                                 │    │
                          │   │     analytic fallback model (built-in) │    │
                          │   └───────────────────────────────────────┘    │
                          │                    │  scores / rankings         │
                          │                    ▼                            │
                          │  decision hooks (mlHooks in mlCmd.c + guarded   │
                          │  call in abcResub.c): reorder candidates,       │
                          │  gate windows — correctness checks UNCHANGED    │
                          └──────────────────────────────────────────────┘

        Offline (Python, GPU):   data (mlData.c dumps) ──▶ train SYNAPSE ──▶ export ONNX
```

Two deployment modes, chosen at build time:

| Build | Inference backend | Purpose |
|-------|-------------------|---------|
| default (`make`) | **analytic fallback** model in `mlInfer.c` | hooks run end-to-end with *zero* ML dependencies — you can test the whole pipeline today, on any machine, no GPU, no libraries |
| `make ABC_USE_ONNX=1` | **ONNX Runtime** C API loading a trained `synapse.onnx` | real neural inference once a model is trained |

The analytic fallback is not a throwaway: it is a transparent, hand-derived
approximation of what each head *should* output (e.g. potential ≈ normalized MFFC
× level-slack). It lets us validate plumbing, feature correctness, and the
re-ranking machinery before a single GPU-hour is spent, and it doubles as the
"heuristic baseline" in ablations.

---

## 3. The SYNAPSE neural model (Python, `python/models/`)

### 3.1 Shared encoder — `encoder.py`
A message-passing GNN over the AIG. We provide four interchangeable backbones so
you can benchmark them:

1. `GCNEncoder`   — vanilla GCN (baseline).
2. `SAGEEncoder`  — GraphSAGE (inductive, scales to unseen circuits).
3. `GATEncoder`   — graph attention (learns which fanins matter).
4. `AIGConvEncoder` — **our custom DeepGate-style layer**: separate aggregation
   for the two AIG fanins, complement-aware edge gating, and a GRU state update
   run for `T` reversible propagation steps (forward from PIs, backward from POs).
   This is the recommended encoder — it respects AIG semantics (AND + inversion)
   instead of treating the circuit as a generic graph.

Output: a `D_emb`-dimensional embedding per node (default 64).

### 3.2 Task heads — `heads.py`
- `PotentialHead`: `emb → scalar` — the **non-myopic value** (Weakness 1).
- `RankHead`: `[root_emb ‖ cand_emb ‖ pair_feats] → score` — candidate re-ranking
  (Weakness 2), used for divisors/cuts/windows.
- `PolicyHead`: `emb → 4 logits` over {rewrite, refactor, resub, skip} — per-node
  transform selection (for the orchestration hook / future RL).

### 3.3 Full model — `synapse.py`
`SynapseModel = encoder + {potential, rank, policy}` with a forward that returns
all three outputs; multi-task loss shares the encoder. Also exposes
`export_ranker_submodel()` and `export_potential_submodel()` that produce the
*small* graphs actually shipped to the C runtime (we don't run the full GNN inside
the hot loop — see §5).

---

## 4. Feature specification (must stay in sync: C ↔ Python)

Defined once in `python/config.py` and mirrored in `ml_abc.h`.

**Node features — `NODE_FEAT_DIM = 16`** (all normalized to ~[0,1]):
| # | feature | rationale |
|---|---------|-----------|
| 0 | level / maxLevel | position in depth |
| 1 | reverseLevel / maxLevel | slack to outputs |
| 2 | log1p(fanout) / log1p(maxFanout) | reuse pressure |
| 3 | fanin0 complemented | AIG polarity |
| 4 | fanin1 complemented | AIG polarity |
| 5 | fanin0 is CI | boundary proximity |
| 6 | fanin1 is CI | boundary proximity |
| 7 | log1p(MFFC size) / norm | how much this node "owns" |
| 8 | #fanouts that are POs / fanout | output criticality |
| 9 | level slack proxy (maxLevel-level-revLevel) | timing headroom |
| 10 | dist-to-nearest-PI / maxLevel | logic depth |
| 11 | log1p(r2 AND count) / norm | local density |
| 12 | fraction of fanouts complemented | inversion context |
| 13 | on-critical-path flag | timing |
| 14 | reconvergence flag (fanouts share a grandchild) | resub/mfs opportunity |
| 15 | constant 1 (bias) | — |

**Divisor/candidate pair features — `DIV_FEAT_DIM = 12`**: level diff, structural
distance, simulation-signature agreement (Hamming over sim words), unateness flags,
shared-support size, is-in-TFI, etc. (full list in `mlFeatures.c`).

**Edge attribute — `EDGE_ATTR_DIM = 1`**: fanin complement bit.

---

## 5. Deployment strategy — keeping it fast enough for synthesis

Running a full GNN per node inside `resub` would be far too slow (synthesis makes
millions of local calls). SYNAPSE uses a **two-tier "encode-once, score-many"**
scheme:

1. **Encode once per snapshot:** when a learned pass starts, run the GNN encoder a
   single time over the whole AIG (batched, ~one forward pass) and cache the
   `D_emb` embedding per node in a `Vec` indexed by ObjId. Cost amortized over the
   whole pass.
2. **Score many, cheaply:** the per-candidate `RankHead`/`PotentialHead` are tiny
   MLPs. They read cached embeddings + cheap pair features → a few matrix-vector
   products in C. This is what actually runs in the hot loop, via ONNX or the
   analytic fallback.

This mirrors the "one-shot guidance" insight from SAT literature (NeuroBack, RLAF):
pay the expensive neural cost once, then guide cheaply. It is what makes an
in-tool neural policy viable at all.

---

## 6. Training protocol (offline, GPU — `python/train/`)

### 6.1 Self-supervised encoder pretraining
Before any task, pretrain `AIGConvEncoder` on a large pool of AIGs
(EPFL + OpenABC-D + random) with two objectives (DeepGate-style):
- **Functional:** predict each node's simulated logic-1 probability (truth-density)
  from random input stimuli → forces embeddings to capture *function*, not just
  topology.
- **Structural (contrastive):** NPN-equivalent local cuts should map to nearby
  embeddings.

### 6.2 Supervised head training (no RL needed to start)
Data is generated *for free* by instrumented ABC (`mlData.c`, `ml_collect`):
- **Ranker labels:** run stock `resub`/`mfs`, log every candidate's features and
  whether it was the accepted/best one → learning-to-rank (pairwise/listwise loss).
- **Potential labels (non-myopic):** run the *full* `resyn2` recipe; for each node
  touched at step *t*, attribute the *final* total node reduction back to it
  (Monte-Carlo return with discount γ across passes) → regression target for
  `PotentialHead`. This is the credit-assignment signal that encodes look-ahead.

### 6.3 Optional RL fine-tuning
Wrap ABC (via the Level-1 harness in `04_ML_INTEGRATION_GUIDE.md`) as a Gym env:
state = cached embeddings, action = candidate/transform choice, reward = verified
gain. Fine-tune `PolicyHead` with PPO. Reuses the actor-critic experience from the
MaskPlace macro-placement project.

---

## 7. Evaluation plan
- **Benchmarks:** EPFL combinational, ISCAS'85/89, OpenABC-D IPs.
- **Baselines:** stock `resyn2`, `resyn2rs`, `&syn2`; ML baselines SLAP/DRiLLS.
- **Metrics:** AIG node count, level (depth), and — crucially — **post-mapping**
  area/delay after `if -K6` and LUT-6, plus wall-clock runtime.
- **Ablations:** analytic-fallback vs trained; each head on/off; encoder backbone
  comparison; myopic vs non-myopic potential.
- **The claim to prove:** at equal or lower runtime, SYNAPSE-guided flows reach
  lower area/delay than stock ABC and than prior single-task ML methods, and the
  *same* pretrained encoder helps *multiple* passes.

---

## 8. Novelty vs prior art (verified against 2024–2026 literature)
| Prior work | Granularity | Shared encoder? | Non-myopic? | In-tool native? |
|---|---|---|---|---|
| DRiLLS / ABC-RL | recipe (whole net) | no | partial (recipe RL) | wrapper |
| SLAP / LEAP / DeepCut / GPA | cut ranking (mapping only) | no | no | patch to one pass |
| NeuroBack / RLAF | SAT branching | no | one-shot | solver only |
| **SYNAPSE** | **per-node & per-candidate, multi-pass** | **yes** | **yes (value head)** | **yes (ext_ml + ONNX)** |

No surveyed system combines a shared pretrained circuit encoder, a non-myopic
value head for credit assignment across the synthesis recipe, and native in-tool
multi-pass deployment. That intersection is the research contribution.

---

## 9. File map
See `INTEGRATION.md` for build/run details and `STATUS.md` for what is
implemented vs stubbed.
