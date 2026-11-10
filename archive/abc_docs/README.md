# ABC Learning Path — Understand the Codebase Without Getting Lost

ABC (A System for Sequential Logic Synthesis and Verification) is a huge C codebase
(~2,000+ source files under `abc/src`). You do **not** need to read everything.

This documentation teaches ABC as a **flow**: what it is → how data moves → how
commands run → what each package does → which files to open next.

**Your clone:** `hardware_eda/abc`

---

## Start here — the one picture that matters

```
                    ┌─────────────────────────────────────┐
                    │         Abc_Frame_t (global)        │
                    │  command table · aliases · libraries │
                    └──────────────┬──────────────────────┘
                                   │
              ┌────────────────────┼────────────────────┐
              ▼                                         ▼
       pNtkCur : Abc_Ntk_t                        pGia : Gia_Man_t
       "classic world"                            "ABC9 / & world"
       rewrite, resyn2, if, map                   &syn2, &if, &b, &fraig
              │                                         │
              └────────────── &get / &put ──────────────┘
                                   │
                                   ▼
                         read → strash → optimize
                              → map → verify → write
```

**Rule of thumb:** learn the **frame + two graphs + command dispatch** first.
Everything else is an algorithm plugged into that skeleton.

---

## Read in this order (easy flow)

| Step | Doc | Time | You will understand |
|------|-----|------|---------------------|
| 0 | [00_ONE_PAGE_OVERVIEW.md](00_ONE_PAGE_OVERVIEW.md) | 10 min | What ABC does in EDA |
| 1 | [01_END_TO_END_FLOW.md](01_END_TO_END_FLOW.md) | 20 min | Full synthesis pipeline as a story |
| 2 | [02_DIRECTORY_MAP.md](02_DIRECTORY_MAP.md) | 25 min | What each `src/` folder is for (read vs skip) |
| 3 | [03_DATA_STRUCTURES.md](03_DATA_STRUCTURES.md) | 40 min | `Abc_Ntk_t`, `Gia_Man_t`, complemented edges |
| 4 | [04_COMMAND_SYSTEM.md](04_COMMAND_SYSTEM.md) | 30 min | How `rw` / `resyn2` / `&syn2` actually run |
| 5 | [05_OPTIMIZATION_PASSES.md](05_OPTIMIZATION_PASSES.md) | 45 min | balance, rewrite, refactor, resub |
| 6 | [06_MAPPING_AND_PROOF.md](06_MAPPING_AND_PROOF.md) | 30 min | LUT/std-cell mapping + CEC/FRAIG/PDR |
| 7 | [07_HANDS_ON.md](07_HANDS_ON.md) | 45 min | Build + run real sessions |
| 8 | [08_READING_PLAN.md](08_READING_PLAN.md) | ongoing | Day-by-day source reading plan |

**Optional (research / ML):** see
[`../ml_for_eda_research/abc_deep_dive/`](../ml_for_eda_research/abc_deep_dive/)
for heuristic injection points and ML integration.

**Official links:**
- https://people.eecs.berkeley.edu/~alanmi/abc/
- https://github.com/berkeley-abc/abc
- Getting started PDF (Ana Petkovska): linked from `abc/README.md`

---

## Survival rules for a huge codebase

1. **Never start in `sat/` or `bdd/`** — those are engines ABC *calls*, not the story.
2. **Always start from a command** — type it in the shell, then grep its name in `src/base/abci/abc.c`.
3. **Two worlds, same tool** — classic commands vs `&`-prefixed GIA commands. Bridge with `&get` / `&put`.
4. **Scripts live in `abc.rc`** — `resyn2` is not magic C code; it is an alias chain.
5. **Learn `Vec_*` macros once** (`src/misc/vec/`) — then half the code becomes readable.

---

## Quick “where is X?” cheat sheet

| I want to know… | Open this |
|-----------------|-----------|
| Entry / REPL | `src/base/main/main.c`, `mainReal.c` |
| Global state | `src/base/main/mainInt.h` → `Abc_Frame_t` |
| Command dispatch | `src/base/cmd/` |
| Classic AIG network | `src/base/abc/abc.h`, `abcAig.c` |
| All command wrappers | `src/base/abci/abc.c` (huge) |
| Modern scalable AIG | `src/aig/gia/gia.h` |
| Rewrite engine | `src/opt/rwr/` |
| FPGA LUT mapper | `src/map/if/` |
| Recipes / aliases | `abc.rc` |
| Library embedding demo | `src/demo.c` |
