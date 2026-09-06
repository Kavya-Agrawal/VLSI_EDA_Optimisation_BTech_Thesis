# Chip Placement with Deep Reinforcement Learning (Google, 2020)

- **Authors:** A. Mirhoseini, A. Goldie, et al. (Google Brain)
- **Venue / Year:** arXiv 2020 → later published as *"A Graph Placement Methodology for Fast Chip Design"*, **Nature 2021**
- **PDF:** `ChipPlacement_DeepRL_Google2020.pdf`
- **Link:** https://arxiv.org/abs/2004.10746
- **Read it first?** ✅ Yes — this is the paper that **started the whole ML-for-placement field**.

---

## TL;DR (one breath)
Google framed **macro placement** as a game an AI agent learns to play: place one macro at a time on a grid to minimize wirelength + congestion. Crucially, it **learns from past chips**, so it gets faster and better on new chips — producing placements comparable to or better than human experts in **under 6 hours** instead of weeks.

## The problem (plain English)
- A chip is a **netlist**: a huge graph of components (macros = big blocks like memories; standard cells = tiny logic gates) connected by wires.
- **Placement** = decide where every component sits on the 2D chip. This decides speed, power, and area (**PPA**).
- Doing it well takes human engineers **weeks**, and classic tools don't "learn" — every new chip starts from zero.

## Key idea
Treat placement as a **Reinforcement Learning (RL)** problem:
- **State** = the partially-placed chip.
- **Action** = where to put the next macro.
- **Reward** = negative (wirelength + congestion) once everything is placed.
The agent plays this "game" thousands of times and improves.

## How it works (the clever parts)
1. **Place macros with RL** (the hard, high-impact blocks), then let a fast classic tool place the millions of standard cells.
2. **Edge-GNN encoder:** a Graph Neural Network reads the netlist and produces a rich embedding of the chip. This is what lets the model **generalize to unseen chips**.
3. **Transfer learning:** train the encoder on many chips by learning to *predict placement quality*. Pre-trained agents then place new chips much faster.

## Results (headline numbers)
- Placements **superhuman or comparable** to human experts on real Google TPU blocks.
- Generates a placement in **< 6 hours** vs. weeks for humans.
- Gets **better the more chips it sees** (positive transfer).

## Why it matters for your BTP
- This is the **conceptual ancestor** of MaskPlace, ChiPFormer, MacroRegulator, etc. Read it to understand the "place-one-macro-at-a-time as an MDP" formulation that everything else reacts to.
- Its weaknesses (slow online RL, needs retraining per chip, GNN can't see pin offsets) are **exactly what later papers fix** — so it frames the research gaps.

## Limitations
- Online RL is **slow and sample-hungry**; retrains for each new design family.
- Sparse reward (only at the end of an episode) makes learning hard.
- Later independent reproductions (e.g. TILOS MacroPlacement) debated how much it beats strong classic baselines.

## Mini-glossary
- **Macro:** large pre-designed block (SRAM, IO, compute unit).
- **Standard cell:** tiny logic gate (AND, flip-flop…). Millions per chip.
- **Netlist:** graph of components + wires (a *hypergraph*).
- **HPWL:** Half-Perimeter Wire Length — a fast wirelength estimate.
- **PPA:** Power, Performance, Area — the 3 goals of chip design.
- **MDP:** Markov Decision Process — the math framework behind RL.
