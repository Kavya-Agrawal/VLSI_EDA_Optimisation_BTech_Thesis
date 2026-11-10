# Machine Learning for Electronic Design Automation: A Survey

- **Authors:** Guyue Huang, Jingbo Hu, Yifan He, et al.; Xuefei Ning, Yu Wang (Tsinghua University)
- **Venue / Year:** **ACM TODAES 2021**
- **PDF:** `ML_for_EDA_Survey_TODAES2021.pdf`
- **Link:** https://arxiv.org/abs/2102.03357
- **Best "big picture" starting point.** 🗺️

---

## TL;DR (one breath)
A broad map of **how ML is applied across the entire chip-design flow** — high-level synthesis, logic synthesis, placement, routing, testing, verification, and more. Read this to understand **where your work fits** in the larger landscape and what problems each stage poses for ML.

## What it covers
Organized by **design stage** and by **ML role**:
- **Where:** HLS, logic synthesis, floorplanning/placement, routing, timing/power/IR analysis, mask synthesis/OPC, testing & verification.
- **How ML is used:** as a **predictor** (estimate an expensive metric fast), as a **decision-maker/optimizer** (RL to make design choices), and as a **generator**.

## Key framing (useful mental models)
- **ML for prediction vs. ML for optimization:** many EDA wins come from replacing a slow tool with a **fast learned estimator** (e.g., predict congestion/timing early). Others use **RL** to make sequential design decisions (placement, synthesis recipes).
- **Cross-stage prediction:** predict a *late-stage* metric from *early-stage* data to shorten the design loop.

## Why it matters for your BTP
- The **orientation document** — read it first to place MaskPlace/ChiPFormer/DRiLLS/CircuitNet in context.
- Its taxonomy is a ready-made **structure for your thesis's related-work chapter**.

## Limitations
- **2021 snapshot** — predates the diffusion/LLM/foundation-model wave (fill gaps with the newer papers in this compendium).

## Mini-glossary
- **EDA:** Electronic Design Automation — the software tools that design chips.
- **HLS:** High-Level Synthesis — C/C++ → hardware.
- **OPC:** Optical Proximity Correction — mask-making step in manufacturing.
- **Cross-stage prediction:** using early data to predict later-stage outcomes.
