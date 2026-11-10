# Chip Placement with Diffusion Models

- **Authors:** Vint Lee, Minh Nguyen, Leena Elzeiny, Chun Deng, Pieter Abbeel, John Wawrzynek (UC Berkeley et al.)
- **Venue / Year:** **ICML 2025**
- **PDF:** `ChipDiffusion_ICML2025.pdf`
- **Link:** https://arxiv.org/abs/2407.12282 · Code: https://github.com/vint-1/chipdiffusion
- **This is the newest paradigm** in learned placement.

---

## TL;DR (one breath)
Drop RL entirely. Train a **diffusion model** (like the tech behind AI image generators) to **generate a whole placement at once**, and steer it toward good layouts with **guided sampling**. It places **new chips zero-shot** (no per-chip retraining), trained on **synthetic data**.

## The problem it fixes
RL placers are **slow, sample-inefficient, and don't generalize** — they treat each chip as a new task and place components **one-by-one** (an early bad choice can't be undone). Also, real placement data is scarce/proprietary.

## Key idea — generate the layout, don't sequence it
- A **diffusion model** learns to turn random noise into a valid placement of **all** components simultaneously.
- **Guided sampling** biases the generation toward low-wirelength, low-overlap layouts (like classifier guidance in image diffusion).
- Trained **offline at scale**, then used **zero-shot** on unseen circuits.

## How it works
1. **Synthetic data generator:** since real netlists are scarce, they invent a way to generate large synthetic circuit datasets, and study which design choices make models **generalize** to real chips.
2. **Efficient denoising architecture** designed to scale to many components.
3. At inference, **guide** the denoising steps with placement objectives (wirelength/overlap) → high-quality layout in one generative pass.

## Results (headline numbers)
- **Zero-shot** placement on unseen, realistic circuits.
- **Competitive with state-of-the-art** placers — without online RL and without per-chip training.

## Why it matters for your BTP
- Represents the **frontier alternative** to your RL approach. If per-chip retraining is your bottleneck, diffusion + guidance is the escape hatch.
- The **synthetic-data-generation** recipe is independently useful (data scarcity is *the* problem in ML-for-EDA).

## Limitations
- Guidance quality depends on good differentiable objectives.
- Synthetic→real generalization is delicate (the paper spends effort on exactly this).

## Mini-glossary
- **Diffusion model:** generative model that denoises random noise into a structured output.
- **Guided sampling:** nudging the generation with an objective/gradient at each denoise step.
- **Zero-shot:** works on a new input with no additional training.
