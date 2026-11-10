# Reinforcement Learning Policy as Macro Regulator Rather than Macro Placer

- **Authors:** Y. Shi, R.-T. Chen, X. Lin, S. Kai, S. Xu, C. Qian, et al. (Nanjing Univ. LAMDA + Huawei Noah's Ark)
- **Venue / Year:** **NeurIPS 2024**
- **PDF:** `MacroRegulator_NeurIPS2024.pdf`
- **Link:** https://arxiv.org/abs/2412.07167 · Code: https://github.com/lamda-bbo/macro-regulator
- **Very relevant to:** your "better macro ordering / action space" ideas.

---

## TL;DR (one breath)
Don't make RL place macros **from scratch** (hard, sparse rewards). Instead, start from an existing placement and let RL **nudge/refine** it — a "regulator," not a "placer." This gives **dense, accurate rewards**, adds a **regularity** objective the industry cares about, and yields real **PPA** gains. It can polish the output of *any* placer (including yours).

## The problem it fixes
Placing from an empty canvas means the agent gets almost **no useful feedback until the end** (sparse reward) and can't undo early mistakes. That's why RL placers are slow and don't guarantee good PPA.

## Key idea — refine, don't create
Reframe the task as **refinement**: given a decent starting layout, the RL policy learns *how to adjust* macro positions. Because the layout is already mostly valid, every small move produces **dense and precise reward signals**.

## How it works
1. Take an initial placement (from any method).
2. RL policy proposes **adjustments** to macros to reduce wirelength and improve **regularity** (macros aligned/organized like a human would do — matters for real chips but usually ignored by RL).
3. Evaluate on real PPA via commercial tools, not just HPWL.

## Results (headline numbers)
- Significant **HPWL + regularity** improvements on **ISPD 2005** and **ICCAD 2015** benchmarks.
- **Real PPA improvements** confirmed with commercial EDA software.
- Acts as a **plug-in refiner** on top of other placers.

## Why it matters for your BTP
- README idea #2 is literally this: *"MaskRegulate-style refinement head on top of your placer + a regularity reward, close the loop to real PPA."*
- You can **bolt this onto your modified MaskPlace** as a second stage to push quality without changing your core placer.

## Limitations
- Needs a reasonable **initial placement** to refine.
- Adds a second training/optimization stage.

## Mini-glossary
- **Regularity:** how neat/aligned the macro arrangement is — a practical manufacturability/quality signal.
- **Dense vs sparse reward:** feedback every step vs only at the end.
- **PPA:** Power, Performance, Area.
