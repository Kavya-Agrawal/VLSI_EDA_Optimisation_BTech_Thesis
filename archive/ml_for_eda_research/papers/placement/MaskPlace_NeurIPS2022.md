# MaskPlace: Fast Chip Placement via Reinforced Visual Representation Learning

- **Authors:** Yao Lai, Yao Mu, Ping Luo (HKU)
- **Venue / Year:** **NeurIPS 2022 (Spotlight)**
- **PDF:** `MaskPlace_NeurIPS2022.pdf`
- **Link:** https://arxiv.org/abs/2211.13382
- **Special note:** 🌟 **This is the base you modified in `macroPlace/`.**

---

## TL;DR (one breath)
Instead of describing a chip as an abstract graph, MaskPlace lets the RL agent **"see" the chip as images (pixel masks)** — like a camera view of where things are and where wires want to go. This visual view + a **dense reward** gives sharper placements with **zero overlaps** and **60–90% shorter wirelength** than earlier RL methods.

## The problem it fixes
Google's method (and DeepPR) encode the chip as a **hypergraph**. Problem: a hypergraph **throws away pin positions** and is expensive, so wirelength estimates are inaccurate and the canvas resolution is tiny. Result: worse, overlapping placements.

## Key idea — placement as "vision"
Represent the chip state as a stack of **pixel-level masks** on a high-res 224×224 grid:
- **Position mask:** which cells are legal (no overlap) for the next macro.
- **Wire mask:** how much wirelength each candidate position would add.
- **View mask:** where already-placed macros are.
The agent is a **CNN** that looks at these masks and picks the best pixel to drop the next macro.

## How it works
1. Place macros one at a time (an MDP), choosing a pixel on the canvas.
2. The **wire mask gives a dense reward** at every step (how much wire this move costs), instead of a single reward at the very end → much easier to learn.
3. The **position mask guarantees legality**, so the final layout has **0% overlap** — no messy legalization needed afterward.

## Results (headline numbers)
- **60–90% wirelength reduction** vs. prior RL methods (GraphPlace, DeepPR).
- **Guaranteed 0% overlap** (a hard constraint others violate).
- Wins on **all** key metrics: wirelength, congestion, density.

## Why it matters for your BTP
- This is your **starting codebase**. Understand the three masks and the dense wire-mask reward deeply — your modifications (expanded action space, better macro ordering) live right here.
- The "wire mask" idea is reused by **WireMask-BBO** (as an evaluator) and refined by **MacroRegulator** — you're in the center of an active line of work.

## Limitations
- Still **online RL trained per circuit** → slow, doesn't transfer to new chips out of the box (ChiPFormer & ChipDiffusion attack this).
- Optimizes **HPWL proxy**, not true routed wirelength / real PPA.

## Mini-glossary
- **Wire mask:** a heatmap image of the extra wirelength each landing spot would create.
- **Dense reward:** feedback every step (vs. *sparse* = only at the end).
- **Legalization (LG):** post-step fix to remove overlaps; MaskPlace avoids needing it.
- **CNN:** Convolutional Neural Network — the standard "vision" model.
