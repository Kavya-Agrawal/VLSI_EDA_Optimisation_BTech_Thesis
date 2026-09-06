# Rethinking Reinforcement Learning based Logic Synthesis

- **Authors:** Chao Wang, Chen Chen, Dong Li, Bin Wang (Huawei Noah's Ark Lab)
- **Venue / Year:** 2022 (arXiv)
- **PDF:** `RethinkingRL_LogicSynthesis_2022.pdf`
- **Link:** https://arxiv.org/abs/2205.07614

---

## TL;DR (one breath)
A **critical, myth-busting** paper. Through careful experiments the authors find that RL logic-synthesis agents (like DRiLLS-style) often learn a policy that **ignores the circuit** and produces a **nearly order-independent** operator sequence. They use this insight to build a simpler, faster method that finds a **common, generalizable recipe** — practical for industry.

## The problem it questions
Everyone was stacking fancier RL on ABC. But **does the agent actually use the circuit state?** The authors suspected the learned policies weren't as "intelligent"/state-aware as claimed.

## Key findings (the "rethink")
1. The learned policy is largely **state-agnostic** — it makes similar decisions regardless of the specific circuit features.
2. The resulting operator sequence is **roughly permutation-invariant** — reordering operators barely changes the result.
→ So much of the RL machinery is **overkill**.

## Their method
- **Automatically identify the critical operators** that actually matter.
- Produce a **common operator sequence** that **generalizes to unseen circuits** (no per-circuit retraining).
- Result: good delay reduction with **much lower runtime**.

## Results
- Verified on the **EPFL benchmark**, a private dataset, and an **industrial-scale** circuit.
- Achieves a strong **delay/area/runtime tradeoff** — practical for real use.

## Why it matters for your BTP
- **Read this before over-engineering an RL synthesis agent.** It tells you *what actually drives QoR* and warns against complexity that doesn't help.
- Motivates evaluating whether your (placement or synthesis) RL policy is **genuinely state-aware** — a great ablation/analysis to include in a thesis.

## Limitations
- Findings are about the studied settings/benchmarks; newer state-aware methods (e.g. ABC-RL with retrieval+MCTS) may behave differently.

## Mini-glossary
- **State-agnostic policy:** picks actions almost independent of the input — a red flag for "is it really learning?".
- **Permutation-invariant sequence:** order of operations doesn't much change the outcome.
- **Operator:** an ABC transform (rewrite, refactor, balance, resub…).
