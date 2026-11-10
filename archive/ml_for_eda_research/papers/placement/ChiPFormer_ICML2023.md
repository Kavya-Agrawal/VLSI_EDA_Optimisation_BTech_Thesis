# ChiPFormer: Transferable Chip Placement via Offline Decision Transformer

- **Authors:** Yao Lai, Jinxin Liu, Zhentao Tang, Bin Wang, Jianye Hao, Ping Luo
- **Venue / Year:** **ICML 2023**
- **PDF:** `ChiPFormer_ICML2023.pdf`
- **Link:** https://arxiv.org/abs/2306.14744
- **Read after:** MaskPlace (same lead author; direct successor).

---

## TL;DR (one breath)
ChiPFormer learns placement **offline** — from a fixed pile of past placement data — using a **Decision Transformer** (the "GPT of RL"). Because it learns a *transferable* policy, adapting to a brand-new chip takes **minutes, not hours** (10× faster), while matching or beating online RL quality.

## The problem it fixes
MaskPlace and Google's method use **online RL**: for every new chip they must interact with the environment thousands of times → **slow** and they **don't transfer** to unseen chips.

## Key idea — treat RL like sequence prediction
A **Decision Transformer** turns RL into "predict the next action given the history and a target return." Train it on **offline** trajectories (states, actions, rewards from many chips). This:
- avoids slow online trial-and-error,
- learns patterns **shared across chips** (multi-task), so it generalizes.

## How it works
1. **Pre-train** the transformer on offline placement data from many circuits (multi-task).
2. For a **new chip**, do a quick **few-shot fine-tune** (as few as 1–300 rollouts) → the policy adapts fast.
3. Places macros autoregressively, conditioned on a desired quality ("return-to-go").

## Results (headline numbers)
- **10× faster** than prior state-of-the-art RL placers.
- **Better placement quality** across **32 circuits** (public + industrial).
- Fine-tuning drops runtime from **hours → minutes**.

## Why it matters for your BTP
- This is the **natural next step from your MaskPlace work**: reframe your expanded-action-space placer as **offline RL** to generalize across benchmarks *without retraining per design*.
- The BTP README explicitly suggests "extend the ChiPFormer/diffusion paradigm to your action space" — this paper is that paradigm.

## Limitations
- Quality depends on the **coverage/quality of the offline dataset** (garbage in → garbage out).
- Still needs *some* fine-tuning per chip (though small).

## Mini-glossary
- **Offline RL:** learn only from a fixed logged dataset, no live environment interaction.
- **Decision Transformer:** a transformer that models (return, state, action) sequences to pick actions.
- **Few-shot fine-tuning:** adapting a pre-trained model with very little new data.
- **Return-to-go:** the remaining reward you're aiming for; used to condition the model.
