# DRiLLS: Deep Reinforcement Learning for Logic Synthesis

- **Authors:** Abdelrahman Hosny, Soheil Hashemi, Mohamed Shalan, Sherief Reda (Brown Univ. + AUC)
- **Venue / Year:** **ASP-DAC 2020**
- **PDF:** `DRiLLS_ASPDAC2020.pdf`
- **Link:** https://arxiv.org/abs/1911.04021 · Code: https://github.com/scale-lab/DRiLLS
- **The canonical RL-for-synthesis paper.**

---

## TL;DR (one breath)
Logic synthesis quality depends heavily on **which sequence of optimization commands** you run in ABC (resub, rewrite, balance…). DRiLLS trains an **Advantage Actor-Critic (A2C)** agent to **discover that sequence automatically**, minimizing area under a delay constraint — beating hand-tuned "recipes" by ~13%.

## The problem (plain English)
Tools like **ABC** transform a circuit (an **AIG**) by applying operations one after another. The **order matters enormously**, and the number of possible orderings is astronomically large. Engineers hand-craft "recipes" (like `resyn2`); finding better ones is a black art.

## Key idea — learn the recipe with RL
Treat recipe construction as an MDP:
- **State** = features of the current AIG (counts of ANDs, levels/depth, etc.).
- **Action** = which ABC optimization to apply next.
- **Reward** = area reduction while respecting a **delay (timing) constraint**.

## How it works
1. Extract cheap **circuit features** to describe the current design state.
2. **A2C agent** picks the next transformation; ABC applies it.
3. Reward shaped to **minimize area subject to a delay budget** (a constrained objective).
4. Trains without humans in the loop.

## Results (headline numbers)
- **~13% average QoR improvement** over prior exploration methods on the **EPFL benchmark suite**.
- Fully **autonomous** recipe discovery.

## Why it matters for your BTP
- README direction #3: **RL over ABC** is a clean, low-compute research area — and DRiLLS is the entry point.
- You already have **ABC in this repo** (`abc/`) + the deep-dive notes → you can reproduce/extend DRiLLS directly (e.g., better state features, MCTS, retrieval — see ABC-RL).

## Limitations
- Learns **per-circuit** (limited transfer) — later work (ABC-RL, "Rethinking RL") tackles generalization.
- Hand-chosen features; sensitive to reward shaping.

## Mini-glossary
- **Logic synthesis:** turning a Boolean/RTL description into an optimized gate netlist.
- **AIG:** And-Inverter Graph — the compact circuit representation ABC optimizes.
- **QoR:** Quality of Results (area, delay, power).
- **A2C:** Advantage Actor-Critic — a policy-gradient RL algorithm.
- **Recipe:** an ordered list of synthesis commands.
