# POLYPHONY — Status

Branch: `feature/genesis-neural-synthesis`

| Piece | Status |
|-------|--------|
| NP-hard hotspot catalogue | ✅ `docs/NP_HARD_HOTSPOTS.md` |
| Design (diverse generative choices) | ✅ `docs/DESIGN.md` |
| C: program TT eval + GIA decode | ✅ `polyTruth.c` |
| C: fallback diverse synthesizer | ✅ `polySynth.c` |
| C: cut extraction | ✅ `polyCuts.c` |
| C: commands + frame registration | ✅ `polyCmd.c` / `polyCore.c` |
| C: module.make | ✅ |
| Python verifier | ✅ |
| Generator (GRU policy) | ✅ scaffold |
| GFlowNet / demo trainer | ✅ scaffold (`--mode demo` works without torch) |
| ONNX export | 🟡 needs torch |
| Sibling choice injection into `&if` | ⬜ documented next step |
| GPU training on EPFL | ⬜ not run (no GPU) |

Default path runs with **zero ML deps** (fallback synthesizer + exact verifier).
