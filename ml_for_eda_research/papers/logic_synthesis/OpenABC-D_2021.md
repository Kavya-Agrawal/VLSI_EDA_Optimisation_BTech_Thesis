# OpenABC-D: A Large-Scale Dataset for Machine Learning Guided Integrated Circuit Synthesis

- **Authors:** Animesh Basak Chowdhury, Benjamin Tan, Ramesh Karri, Siddharth Garg (NYU)
- **Venue / Year:** 2021
- **PDF:** `OpenABC-D_2021.pdf`
- **Link:** https://arxiv.org/abs/2110.11292 · Code/data: https://github.com/NYU-MLDA/OpenABC

---

## TL;DR (one breath)
ML-for-synthesis was held back by **no standard dataset**. OpenABC-D fixes that: it runs **ABC** with **1,500 synthesis recipes** over many open-source designs and records the intermediate **AIGs + labels (area/delay)** — a ready-made, graph-structured dataset for training GNNs to predict/guide synthesis.

## The problem it fixes
Every ML-for-synthesis paper built its **own tiny private dataset**, so results weren't comparable or reproducible. There was no "ImageNet for logic synthesis."

## Key idea — a big, labeled, graph dataset
Systematically synthesize many circuits under many recipes and **save everything** in a form ML can consume:
- The **AIG graphs** at each step (nodes/edges).
- The resulting **QoR labels** (area, delay).
- Metadata to define standard **ML tasks** (e.g., predict final QoR from an AIG + recipe).

## What's in it
- **~870k+ AIG graphs** generated from **1,500 recipes** applied to **29 open-source designs**.
- Preprocessed for **PyTorch Geometric** (GNN-ready).
- Benchmark tasks like **QoR prediction**.

## Results / contribution
- A reusable, public **benchmark** enabling apples-to-apples comparison.
- Baseline GNN models for predicting synthesis outcomes.

## Why it matters for your BTP
- If you go the **logic-synthesis** route, this is your **training data** — no need to generate your own.
- Pairs perfectly with **DRiLLS/ABC-RL**: train a GNN QoR predictor here, use it as a **fast reward** for RL recipe search.

## Limitations
- Labels come from ABC proxies, not full physical PPA.
- Dataset is large (storage/compute to use fully).

## Mini-glossary
- **AIG:** And-Inverter Graph.
- **Recipe:** ordered sequence of ABC optimizations.
- **QoR:** Quality of Results.
- **GNN / PyTorch Geometric:** graph neural nets and the library to train them.
