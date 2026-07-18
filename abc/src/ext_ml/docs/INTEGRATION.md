# SYNAPSE — Integration & Usage Guide

How the module plugs into ABC, how to build it (with/without ONNX), the command
reference, and the end-to-end data→train→deploy loop.

---

## 1. How it hooks into ABC (no fork of the core needed)

The module lives entirely in `abc/src/ext_ml/`. ABC's Makefile auto-discovers any
`src/ext*` directory (`MODULES := $(wildcard src/ext*) ...`) and includes its
`module.make`, so the module is compiled into `abc`/`libabc` automatically.

Registration happens **before `main()`** via a GCC/Clang constructor in
`mlCore.c` that installs an `Abc_FrameInitializer_t`. When the ABC frame starts,
`Ml_Register()` adds the `ml_*` commands. No edit to the giant `abc.c` is needed.

The **only** edit to ABC's core is a tiny, runtime-gated call in
`src/base/abci/abcResub.c` (right after `Abc_ManResubDivsS`): if ML is enabled it
reranks the *already-validated* single-divisor candidate arrays. With ML disabled
(the default) these calls are a single predicate check — stock behaviour is
unchanged.

```
  ext_ml/
    module.make          build integration (SRC += ...)
    ml_abc.h             API + feature spec (mirrors python/config.py)
    mlCore.c             singleton manager + auto-registration
    mlFeatures.c         GIA feature extraction + dump
    mlInfer.c            ONNX backend  OR  analytic fallback
    mlData.c             training-data logging
    mlCmd.c              commands + Ml_HookResub* decision hooks
    python/              model zoo, training, ONNX export
    docs/                DESIGN / INTEGRATION / STATUS
```

---

## 2. Building

### Default (no ML dependencies — works on any machine, incl. this one)
```bash
cd abc
make -j$(nproc)                 # analytic-fallback backend is compiled in
```
Everything runs: feature extraction, node scoring, divisor reranking — driven by
the transparent analytic model in `mlInfer.c`. Great for validating the pipeline
and for the "heuristic baseline" ablation. **No GPU, no libraries.**

### With ONNX neural inference (once you have a trained model)
```bash
# 1. get ONNX Runtime (headers + libonnxruntime)
#    e.g. download the release tarball and set:
export ORT=/path/to/onnxruntime
# 2. build ABC telling it to compile the ONNX path and where to find ORT
make -j$(nproc) \
  ABC_USE_ONNX=1 \
  OPTFLAGS="-g -O2 -DABC_USE_ONNX -I$ORT/include" \
  LIBS="-lm -ldl -lrt -L$ORT/lib -lonnxruntime"
```
> Windows: build under WSL2 (recommended) exactly as above, or link
> `onnxruntime.lib`/`onnxruntime.dll` in the MSVC project. The fallback build
> needs none of this.

---

## 3. Command reference

| Command | Purpose |
|---------|---------|
| `ml_config [-edvx] [-m model.onnx] [-c data.csv]` | enable/disable, verbosity, load model, start/stop data collection, print config |
| `ml_features [-o file]` | dump the current GIA node-feature matrix + edges (needs `&get`) |
| `ml_potential [-N k]` | score GIA nodes by predicted non-myopic value; print top-k |
| `ml_resub` | run classic `resub` with SYNAPSE divisor reranking live |
| `ml_stats` | print runtime counters (nodes scored, candidates reranked, ...) |

### Quick sessions

Inspect features and node value (fallback backend, no training needed):
```
abc> read i10.aig; strash; &get
abc> ml_features -o i10_feats.txt
abc> ml_potential -N 15
```

ML-guided resubstitution vs stock, on the classic network:
```
abc> read i10.aig; strash
abc> ps
abc> ml_resub                 ; # resub with learned divisor ordering
abc> ps
abc> ml_stats
```

Collect training data while running a normal flow:
```
abc> ml_config -c data/resub_divs.csv -e
abc> read i10.aig; strash; resub; resub -K 8
abc> ml_config -x            ; # stop collection
```

Use a trained model (ONNX build):
```
abc> ml_config -m synapse.onnx -e
abc> read i10.aig; strash; ml_resub; ps
```

---

## 4. End-to-end research loop

```
  (1) COLLECT            (2) TRAIN (GPU)             (3) EXPORT           (4) DEPLOY
  ml_config -c data.csv  python -m train.train_*     python -m           ml_config -m
  + run flows            --> checkpoints/*.pt        export.to_onnx      synapse.onnx -e
        │                        │                     --ckpt ...             │
        └── data/graphs (ml_features dumps) ──────────┘                      ▼
                                                                    ml_resub / ml_potential
                                          ┌───────────── EVALUATE ─────────────┐
                                          │ EPFL/OpenABC-D: nodes, levels,      │
                                          │ post-if -K6 area/delay, runtime     │
                                          │ vs stock (ml disabled) = A/B        │
                                          └─────────────────────────────────────┘
```

Smoke-test the ONNX path without any training:
```bash
cd abc/src/ext_ml/python
python -m export.to_onnx --dummy --out /tmp/synapse.onnx   # random weights
# then, in an ABC built with ABC_USE_ONNX:
#   ml_config -m /tmp/synapse.onnx -e ; read i10.aig; strash; ml_resub
```

---

## 5. Where to extend next (more hooks)
- **mfs windowing gate:** call `Ml_InferWindowPayoff` in `src/opt/mfs/mfsCore.c`
  before building each window; skip low-payoff windows. Hook point + features are
  ready (`ML_TASK_MFS_WINDOW`).
- **cut ranking:** call `Ml_InferRankScore` inside `If_ManSortCompare`
  (`src/map/if/ifCut.c`) with `ML_TASK_CUT_RANK`.
- **rewrite subgraph choice:** score candidate subgraphs in `rwrEva.c`.
All reuse the same encoder + heads; only a new feature adapter is needed per pass.
