# POLYPHONY — Integration

## Build
ABC Makefile auto-includes `src/ext*`. After adding this module:
```bash
cd abc && make -j
```
On Windows use WSL2/Linux (recommended). MinGW can syntax-check sources.

Commands register via `Abc_FrameAddInitializer` in `polyCore.c` (GCC/Clang constructor).

## Commands
| Command | Purpose |
|---------|---------|
| `poly_config [-edv] [-n samples] [-k keep] [-g max_gates]` | enable/config |
| `poly_extract [-N show]` | extract k-input cuts + TTs from current GIA (`&get` first) |
| `poly_synth [-K n] [-T hex]` | synthesize diverse verified equivalents of a TT (fallback engine) |
| `poly_stats` | counters |

## Pipeline
1. `&r design.aig` or `read; strash; &get`
2. `poly_extract` — see cuts/truths
3. `poly_synth -K 3` — demo: generate verified XOR equivalents via fallback synthesizer
4. (GPU later) train generator → ONNX → swap into sampling path

## Python
```
cd abc/src/ext_poly/python
python -m tests.test_smoke
python -m train.train_gflownet --mode demo
python -m export.to_onnx --dummy --out polyphony.onnx   # needs torch
```

## Correctness
`polyTruth.c` / `python/verifier.py` evaluate programs by bitwise TT simulation.
Only programs with `Poly_ProgIsEquivalent==1` are kept. Mapping choices never
receive inequivalent alternatives.
