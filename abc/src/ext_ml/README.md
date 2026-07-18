# SYNAPSE

**Synthesis-Aware Neural-Aided Policy for Search & Efficiency** — a neural
optimization co-processor embedded natively inside Berkeley ABC.

SYNAPSE attacks the three structural weaknesses of ABC's greedy local
optimizations with one shared neural substrate:

1. **Myopia** → a *non-myopic value head* that predicts a node's contribution to
   the *final* QoR after the whole recipe (credit assignment across passes).
2. **Fixed candidate ordering** → a *ranking head* that reorders divisors / cuts /
   windows so promising ones are tried first (correctness always preserved by
   ABC's exact checks).
3. **No cross-pass transfer** → one *pretrained AIG foundation encoder* whose node
   embeddings feed every task head.

## Read this first
- `docs/DESIGN.md` — the research idea, architecture, math, novelty vs 2024–26 SOTA.
- `docs/INTEGRATION.md` — build (with/without ONNX), commands, the data→train→deploy loop.
- `docs/STATUS.md` — what's implemented vs stubbed.

## 30-second try (no GPU, no libraries)
```bash
cd abc && make -j$(nproc)
./abc -c "read i10.aig; strash; &get; ml_features -o f.txt; ml_potential -N 10"
./abc -c "read i10.aig; strash; ps; ml_resub; ps; ml_stats"
```
The default build uses a transparent analytic model, so the entire pipeline —
feature extraction, node scoring, divisor reranking — runs immediately and serves
as the heuristic baseline. Swap in a trained neural model later via
`ml_config -m synapse.onnx -e` (ONNX build).

## Layout
```
ml_abc.h      shared API + feature spec        mlCmd.c      commands + hooks
mlCore.c      manager + auto-registration      module.make  build integration
mlFeatures.c  GIA feature extraction           python/      model zoo + training + ONNX export
mlInfer.c     ONNX  OR  analytic fallback       docs/        DESIGN / INTEGRATION / STATUS
mlData.c      training-data logging
```

Default build = zero external dependencies. Neural inference is opt-in
(`make ABC_USE_ONNX=1`). Stock ABC behaviour is unchanged unless you run
`ml_config -e`.
