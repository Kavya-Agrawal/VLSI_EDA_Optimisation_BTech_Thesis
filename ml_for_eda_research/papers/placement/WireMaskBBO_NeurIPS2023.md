# Macro Placement by Wire-Mask-Guided Black-Box Optimization (WireMask-BBO)

- **Authors:** Yunqi Shi, Ke Xue, Lei Song, Chao Qian (Nanjing Univ. LAMDA)
- **Venue / Year:** **NeurIPS 2023**
- **PDF:** `WireMaskBBO_NeurIPS2023.pdf`
- **Link:** https://arxiv.org/abs/2306.16844 · Code: https://github.com/lamda-bbo/WireMask-BBO

---

## TL;DR (one breath)
You don't actually need RL to use MaskPlace's clever "wire mask." WireMask-BBO uses the wire mask inside a **greedy decoder** and lets a simple **black-box optimizer** (evolutionary / Bayesian) search macro orderings. Result: **shorter wirelength in much less time**, and it can **fine-tune any existing placement** (up to **50% HPWL improvement**).

## The problem it fixes
RL placers are **slow to train** and finicky. Packing methods (simulated annealing over B*-trees, sequence pairs) **scale poorly**. Analytical methods **can't guarantee no-overlap**. Can we get RL-level quality without the RL cost?

## Key idea — wire mask as a decoder, BBO as the search
- **Wire-mask-guided greedy procedure:** given an ordering of macros, greedily drop each macro at the pixel that adds the least wirelength (using MaskPlace's wire mask). This deterministically maps an "ordering" → a full placement + its HPWL.
- Now placement is a clean **black-box function** of the ordering → optimize it with any **BBO** algorithm (evolutionary strategies, Bayesian optimization).

## How it works
1. Represent a solution as a **macro order / permutation**.
2. Decode it via the greedy wire-mask procedure → get HPWL.
3. A BBO algorithm proposes better orderings; iterate.
4. **Fine-tuning mode:** seed the optimizer with an existing placement as the initial solution.

## Results (headline numbers)
- **Significantly shorter HPWL** than prior methods **using much less time**.
- **Up to 50% HPWL improvement** when used to fine-tune existing placements.

## Why it matters for your BTP
- **Directly relevant** to your "better macro ordering" idea — it *isolates ordering as the decision variable* and optimizes it explicitly.
- A strong, cheap **baseline** to compare your RL placer against, and a **fine-tuner** you can run on your outputs.
- Same lab as MacroRegulator → these two combine naturally.

## Limitations
- Greedy decoding is a heuristic (not globally optimal).
- Optimizes **HPWL**, not full routed PPA.

## Mini-glossary
- **Black-Box Optimization (BBO):** optimize a function you can only *evaluate*, not differentiate (e.g. evolutionary algorithms).
- **Greedy decoding:** build a solution step-by-step, always taking the locally best choice.
- **Permutation/ordering:** the sequence in which macros are placed.
