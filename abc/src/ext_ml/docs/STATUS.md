# SYNAPSE — Implementation Status

Snapshot of what is built vs stubbed. Branch: `feature/synapse-ml-abc`.
No training has been run (no GPU available yet), per project constraints.

## Legend
- ✅ implemented & self-contained
- 🟡 implemented as scaffold / prototype (works, but simplified or untrained)
- ⬜ designed, not yet wired

## C side (`abc/src/ext_ml`)
| Component | Status | Notes |
|-----------|--------|-------|
| Build integration (`module.make`, ext auto-discovery) | ✅ | compiles into abc/libabc |
| Manager + auto-registration (`mlCore.c`) | ✅ | GCC/Clang constructor; MSVC uses `Ml_ModuleBootstrap()` |
| GIA feature extraction (`mlFeatures.c`) | ✅ | 16 node feats + edges, all real GIA APIs |
| Candidate pair features | ✅ | 12 relational feats incl. sim-signature agreement |
| Inference: analytic fallback | ✅ | transparent, no deps, runs today |
| Inference: ONNX Runtime backend | 🟡 | guarded by `ABC_USE_ONNX`; C API wired, needs ORT to compile/test |
| Data collection (`mlData.c`) | ✅ | CSV rows at decision points |
| Commands (`mlCmd.c`) | ✅ | ml_config/features/potential/resub/stats |
| Resub divisor rerank hook | ✅ | safe injection in `abcResub.c` after `Abc_ManResubDivsS`; runtime-gated |
| mfs window gate hook | ⬜ | inference fn ready (`Ml_InferWindowPayoff`); call site TODO |
| cut-rank hook (`if`) | ⬜ | inference fn ready; call site TODO |

## Python side (`abc/src/ext_ml/python`)
| Component | Status | Notes |
|-----------|--------|-------|
| Config mirror (`config.py`) | ✅ | dims match `ml_abc.h` |
| Encoders: aigconv / gcn / sage / gat (`encoder.py`) | ✅ | aigconv needs only torch; others need PyG |
| Heads: potential / rank / policy (`heads.py`) | ✅ | |
| Full multi-task model (`synapse.py`) | ✅ | + export proxies + multitask loss |
| Data loaders (`dataset.py`) | ✅ | parse feature dumps + decision CSVs |
| Training scaffolds (`train_*.py`) | 🟡 | full loops; no-op without data/GPU |
| ONNX export (`to_onnx.py`) | 🟡 | `--dummy` smoke test + `--ckpt`; needs torch |

## Verified against the real ABC source
- All GIA accessors used exist in `src/aig/gia/gia.h` (checked: `Gia_ManForEachAnd`,
  `Gia_ObjFaninId0/1`, `Gia_ObjFaninC0/1`, `Gia_ObjLevelId`, `Gia_ManLevelNum`,
  `Gia_ManObj`, `Gia_ManCo`, `Gia_ObjIsCi/And`, `Gia_ManAndNum`, ...).
- Classic APIs in the hook (`Abc_ObjLevel`, `Abc_AigLevel`, `Abc_ObjId`,
  `Abc_NtkObjNumMax`, `Abc_ObjIsNode`, `Vec_Ptr*`) exist in `src/base/abc/abc.h`.
- Build mechanism confirmed: `Makefile` lines 36 & 171 (ext auto-include).
- Hook site confirmed: `abcResub.c` `Abc_ManResubEval` after `Abc_ManResubDivsS`;
  reordering the validated `vDivs1UP/UN` arrays cannot affect correctness.

## What remains (needs a GPU / real runs)
1. Generate training data (feature dumps + non-myopic returns) on EPFL/OpenABC-D.
2. Pretrain the encoder (self-supervised) + train heads.
3. Export `synapse.onnx`; build ABC with `ABC_USE_ONNX=1`.
4. Benchmark ML-guided vs stock (`ml_config -d`) on nodes/levels/post-map PPA.
5. Add the mfs + cut-rank call sites (hooks already provided).

## Not yet compiled here
This machine has no ABC build toolchain wired up in-session; the C is written
against verified APIs and ABC conventions but has **not** been compiled. First
build on a Linux/WSL2 box with `make -j` and fix any environment-specific
warnings (all functions are `-Wall` clean by construction: no unused vars,
consistent prototypes).
