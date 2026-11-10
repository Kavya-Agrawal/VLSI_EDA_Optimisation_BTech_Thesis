# 08 — Source Reading Plan (2–3 weeks)

Goal: go from zero to “I can trace any command and modify a pass” **without**
reading all ~2300 files.

All paths relative to `hardware_eda/abc/`.

---

## Week 1 — Skeleton + one full classic pass

| Day | Read / do | Outcome |
|-----|-----------|---------|
| 1 | This doc pack `00`–`02`; skim `abc.rc` | mental model + folder map |
| 2 | `src/base/main/mainReal.c`, `mainInt.h` | frame + startup |
| 3 | `src/base/cmd/` (command execute + alias) | dispatch |
| 4 | `src/base/abc/abc.h` structs + inlines only | `Abc_Ntk_t` / `Abc_Obj_t` |
| 5 | `src/base/abc/abcAig.c` (strash / And) | complemented edges + hashing |
| 6 | Hands-on Session A (`07_HANDS_ON`) | muscle memory |
| 7 | `abci/abc.c` find `rewrite` → `abcRewrite.c` → `opt/rwr/rwrEva.c` | **one pass end-to-end** |

---

## Week 2 — Rest of `resyn2` + GIA

| Day | Read / do | Outcome |
|-----|-----------|---------|
| 8 | `abcBalance.c`, `abcRefactor.c` | balance + refactor |
| 9 | `abcResub.c` (+ skim `opt/res/`) | resubstitution |
| 10 | `src/aig/gia/gia.h` structs | GIA layout |
| 11 | `giaHash.c`, `giaScript.c` (`&syn2`) | GIA synthesis |
| 12 | Hands-on Session B + C | GIA + CEC |
| 13–14 | `src/map/if/if.h`, `ifCore.c`, `ifMap.c` | priority-cut mapping |

---

## Week 3 — Verification hooks + extension readiness

| Day | Read / do | Outcome |
|-----|-----------|---------|
| 15 | `proof/cec` high-level + one call path | miter mindset |
| 16 | Skim `proof/fra` or `dch` | fraig / choices |
| 17 | `src/demo.c`, `abcapis.h` | library embedding |
| 18 | Pick **one** constant in rewrite (cut limit / gain) and change + CEC | confident editing |
| 19–21 | Optional: ML deep dive pack under `ml_for_eda_research/abc_deep_dive/` | research path |

---

## How to read an ABC `.c` file

1. Read the **header comment** (`Synopsis`, `Purpose`).
2. Jump to the **exported** function named like the pass.
3. Find the **main loop** (`Abc_NtkForEachNode` / `Gia_ManForEachAnd`).
4. Find the **accept/reject** condition (gain, cost, SAT result).
5. Only then chase helpers.

---

## What success looks like

You can:

- [ ] Explain classic vs GIA and use `&get` / `&put`
- [ ] Expand `resyn2` and say what each step does
- [ ] Find any command implementation in &lt; 2 minutes
- [ ] Trace `rewrite` from CLI to gain test
- [ ] Run `cec` before/after a change
- [ ] Point to where `if` ranks cuts

If all boxes are checked, you “understand ABC” at the engineering level.
Deep expertise in every SAT solver is **not** required.

---

## When stuck

| Symptom | Try |
|---------|-----|
| Cannot find command | grep `Cmd_CommandAdd` + name in `abci/abc.c` |
| Wrong network empty | check classic vs GIA; try `&get` / `&put` |
| Code unreadable | learn `Vec_IntForEachEntry` macros first |
| Too many files | return to this plan; do not browse `sat/` yet |

---

## Related docs in this repo

| Pack | Focus |
|------|-------|
| `abc_docs/` (here) | understand ABC as a system |
| `ml_for_eda_research/abc_deep_dive/` | heuristics + ML research hooks |

Official:

- https://people.eecs.berkeley.edu/~alanmi/abc/
- https://github.com/berkeley-abc/abc
