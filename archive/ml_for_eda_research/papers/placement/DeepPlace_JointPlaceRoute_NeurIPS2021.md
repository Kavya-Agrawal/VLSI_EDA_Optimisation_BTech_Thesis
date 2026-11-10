# On Joint Learning for Solving Placement and Routing in Chip Design (DeepPlace / DeepPR)

- **Authors:** Ruoyu Cheng, Junchi Yan (SJTU)
- **Venue / Year:** **NeurIPS 2021**
- **PDF:** `DeepPlace_JointPlaceRoute_NeurIPS2021.pdf`
- **Link:** https://arxiv.org/abs/2111.00234 · Code: https://github.com/Thinklab-SJTU/EDA-AI

---

## TL;DR (one breath)
Two methods in one paper: **DeepPlace** learns to place **macros (RL) + standard cells (gradient optimizer)** end-to-end, and **DeepPR** learns to do **placement *and* routing together**. The insight: placement and routing are tightly coupled, so learning them **jointly** beats treating them separately.

## The problem it fixes
Most learned placers handle **only macros** or **only cells**, and ignore routing — even though routing quality is what ultimately matters. There was no end-to-end "place everything, then route" learning pipeline.

## Key idea — joint, end-to-end learning
- **DeepPlace:** RL agent places macros sequentially, then a **gradient-based optimizer** arranges the millions of standard cells — combined into one pipeline.
- **DeepPR:** a single RL framework does **macro placement + routing**, so routing feedback informs placement.

## How it works
- A **multi-view embedding** encodes both **global (graph-level)** and **local (node-level)** structure of the netlist.
- **Random Network Distillation (RND)** adds a curiosity bonus to encourage **exploration** (helps with sparse rewards).
- Trains within a few hours on public benchmarks.

## Results (headline numbers)
- First learning approach to **jointly place macros + standard cells**.
- DeepPR jointly learns **placement and routing**, providing intermediate placements usable by downstream cell placement.

## Why it matters for your BTP
- Foundational for the **"joint place-and-route"** direction and for the **awesome-ai4eda** lineage (PRNet is the follow-up).
- Shows the **exploration trick (RND)** that helps sparse-reward placement RL — useful if your agent struggles to explore its expanded action space.

## Limitations
- Early-stage; scalability and true routed-PPA fidelity are limited vs later work.
- Grid/resolution and reward simplifications.

## Mini-glossary
- **Routing:** drawing the actual wires between placed components.
- **Random Network Distillation (RND):** an exploration bonus that rewards visiting novel states.
- **Multi-view embedding:** combining global-graph and local-node features.
