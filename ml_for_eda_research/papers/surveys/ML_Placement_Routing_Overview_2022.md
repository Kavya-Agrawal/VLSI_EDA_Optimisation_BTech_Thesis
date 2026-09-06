# Towards Machine Learning for Placement and Routing in Chip Design: A Methodological Overview

- **Authors:** Junchi Yan, Xianglong Lyu, Ruoyu Cheng (SJTU), Yibo Lin (PKU)
- **Venue / Year:** 2022 (arXiv)
- **PDF:** `ML_Placement_Routing_Overview_2022.pdf`
- **Link:** https://arxiv.org/abs/2202.13564
- **Focused survey** for *your* two core stages.

---

## TL;DR (one breath)
A **deep dive specifically into ML for placement and routing** (not the whole flow). It organizes the methods, representations, and open challenges — the perfect companion to the broad TODAES survey and the ideal related-work backbone for a placement-focused BTP.

## What it covers
- **Placement:** analytical vs. RL vs. learning-based methods; how the netlist is represented (hypergraph, grid/image, graph embeddings); reward/objective design.
- **Routing:** learning-based global/detailed routing; congestion-aware approaches.
- **Joint place-and-route** learning (the authors wrote DeepPlace/DeepPR).
- **Open problems:** scalability, generalization across designs, reward fidelity, and evaluation methodology.

## Key framing
- Compares **representations** (graph vs. image/grid) — exactly the axis that separates GraphPlace from MaskPlace.
- Highlights the **generalization problem** (per-design retraining) that ChiPFormer/ChipDiffusion later target.

## Why it matters for your BTP
- **Most directly relevant survey** to your MaskPlace-based work — use it to structure your placement related-work and to justify design choices (why images/masks, why dense rewards, why transfer).
- Its "open challenges" list is a **menu of thesis directions**.

## Limitations
- 2022 snapshot — read with the newer placement papers here (MacroRegulator '24, ChipDiffusion '25) for the latest.

## Mini-glossary
- **Placement vs. routing:** decide *where* components go vs. draw *the wires* between them.
- **Representation:** how the chip is encoded for the model (graph, grid, image).
- **Generalization:** performing well on chips not seen in training.
