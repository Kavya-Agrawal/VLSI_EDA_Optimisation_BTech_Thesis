# POLYPHONY — diverse generative synthesis of equivalent subcircuits for choice-based mapping

*A neural generator that learns the **distribution of optimal equivalent
implementations** of a Boolean function and feeds that diversity into ABC's
choice-based technology mapping.*

Branch: `feature/genesis-neural-synthesis`. Module: `abc/src/ext_poly`.
Status: architecture + hooks + a working non-neural fallback; neural training
needs a GPU (not run).

---

## 1. The NP-hard problem and why one circuit is not enough

Finding a **minimum** circuit for a Boolean function (exact synthesis) is
**NP-hard** (`NP_HARD_HOTSPOTS.md` #3). Recent neural work — Circuit Transformer
(ICLR'24), ShortCircuit (AlphaZero'24) — attacks it by generating **one**
near-minimal AIG from a truth table.

But ABC does **not** want one circuit. Its highest-quality flow, **choice-based
mapping** (`dch` + `&if`), deliberately keeps **many structurally-different but
functionally-equivalent** subgraphs ("choices") and lets the covering DP pick the
combination that maps best under the real cost. Choices are how ABC recovers
area/delay that any single structure misses. Today choices come from a few
synthesis snapshots + SAT — expensive and limited in diversity.

> **POLYPHONY's thesis:** the useful object to learn is not *the* minimal circuit
> but the **distribution of good equivalent circuits**. A diversity-seeking
> generator can propose a rich, verified *choice cloud* per cut — precisely the
> input choice-based mapping is starved for. No prior neural-synthesis work
> targets diversity or choice injection; they all optimize a single output.

This also answers the RethinkingRL (2022) critique: the model is **conditioned on
the exact truth table** and every output is **verified equivalent**, so it is
function-aware by construction and can never silently produce a wrong or
circuit-ignoring result.

---

## 2. What POLYPHONY generates

For a k-input cut with target truth table `T` (k ≤ 6 in the prototype), the
generator emits several **circuit programs**, each an exact implementation of `T`:

```
program := list of AND gates, then an output literal
gate g  := (lit_a, lit_b)             # 2-input AND
lit     := 2*node + complement        # node < g  (PIs are nodes 0..k-1)
output  := 2*node + complement
```

This compact "instruction stream" is:
- **decodable** into a GIA sub-AIG via `Gia_ManHashAnd` (with structural hashing,
  so shared logic is reused);
- **verifiable** in microseconds by word-level simulation against `T`
  (see `polyTruth.c`) — *this is the exactness guarantee*;
- **diverse**: different programs = different structures = mapping choices.

Rejected (non-equivalent) samples are simply discarded — correctness is never at
risk, only yield.

---

## 3. The model (Python, `python/`)

### 3.1 Conditional AIG generator — `models/generator.py`
An **encoder–decoder Transformer**:
- **Encoder** embeds the target truth table (2^k bits) + input support info.
- **Decoder** autoregressively emits gate tokens `(lit_a, lit_b)` then the output
  literal, with a **feasibility mask** (a token may only reference already-defined
  nodes; cf. Circuit Transformer's masking) so every sample is a *syntactically
  valid* circuit; functional exactness is then checked by the verifier.

### 3.2 Diversity objective — `train/train_gflownet.py`
Trained as a **GFlowNet** (trajectory-balance loss): the probability of emitting a
program is proportional to a reward `R(program)` that rewards **exactness** and
**compactness** and **novelty vs already-sampled structures**:

```
R = 1[equivalent] * exp(-alpha * size) * (1 + beta * structural_novelty)
```

GFlowNets sample **proportional to reward**, which yields a *set* of high-quality
*diverse* solutions — exactly the choice-cloud objective, and the key departure
from single-best methods (RL/MCTS/supervised) that collapse to one mode.
(A supervised warm-start from ABC's `resyn2`/exact-synthesis solutions and a
PPO/AlphaZero baseline are also provided for ablation.)

### 3.3 Value / size head
Predicts expected minimal size for a truth table — used to prioritise which cuts
are worth generating choices for (skip cuts already optimal).

---

## 4. In-tool deployment (C, `abc/src/ext_poly`)

```
 current GIA ─▶ poly_extract : enumerate k-input cuts, compute truth tables
                                   │
                                   ▼
              generator (ONNX synapse-style) ── OR ── fallback exact synthesizer
              proposes N candidate programs per truth table   (polySynth.c)
                                   │
                                   ▼
              polyTruth.c : simulate each program vs target TT  → keep equivalents
                                   │
                                   ▼
              decode kept programs via Gia_ManHashAnd → equivalent sub-AIGs
                                   │
                                   ▼
              inject as CHOICES (siblings) for choice-based &if mapping
```

Two backends (same as the SYNAPSE module pattern):
- **default build:** a **real, non-neural fallback synthesizer** (`polySynth.c`)
  that produces verified equivalents (SOP/AND-OR, Shannon split, and small
  randomized variants) — so the *entire* extract→synthesize→verify→choices
  pipeline runs today with **zero ML dependencies** and serves as the baseline.
- **`ABC_USE_ONNX=1`:** load the trained POLYPHONY generator and sample programs.

Commands: `poly_config`, `poly_extract`, `poly_synth`, `poly_choices`, `poly_stats`
(see `INTEGRATION.md`).

Choice injection uses GIA's sibling mechanism (`p->pSibls`, cf. `Gia_ManChoiceNum`)
so `&if -C` can consume the generated alternatives; the prototype builds and
verifies the alternatives and reports the diversity/size, with the sibling-linking
step documented as the final integration wiring.

---

## 5. Why this is precise and NP-hard-attacking
- **Precise:** every emitted circuit is checked against the truth table by exact
  simulation; only equivalent ones survive. There is no approximation in the
  output — the *learning* only guides *which* exact structures to propose.
- **NP-hard core:** it explores the exponential space of equivalent multi-level
  implementations, where enumeration/SAT don't scale; the network amortises that
  search into a fast conditional sampler.
- **Knows the problem:** conditioning on the full truth table means the model's
  latent captures the function itself, not surface features.

---

## 6. Evaluation plan
- **Benchmarks:** EPFL, IWLS'23 (Circuit-Transformer's benchmark), OpenABC-D.
- **Baselines:** ABC `dch; &if -C` (stock choices), Circuit-Transformer `ctrw`,
  single-best neural synthesis.
- **Metrics:** post-mapping LUT/area & depth after `&if -C`, number & diversity of
  useful choices, and runtime. **Claim:** more diverse verified choices → better
  post-mapping QoR than stock choices at comparable runtime; and diversity beats
  single-best generation for the *mapping* objective.
- **Ablations:** GFlowNet vs PPO vs supervised; choice count N; cut size k.

## 7. Files
`NP_HARD_HOTSPOTS.md` (problem landscape), `INTEGRATION.md` (build+commands),
`STATUS.md` (done vs stubbed).
