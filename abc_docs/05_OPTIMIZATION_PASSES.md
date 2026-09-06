# 05 — Optimization Passes (tech-independent)

These passes shrink / deepen-reduce the AIG **without** knowing LUTs or standard cells.

All are mostly **greedy local search** with hand-tuned limits.

---

## Big picture

```
strashed AIG
    │
    ├─ balance     rearrange AND trees (depth + sharing)
    ├─ rewrite     replace small cuts by better subgraphs (NPN tables)
    ├─ refactor    collapse a cone → re-factor if smaller
    ├─ resub       express node using nearby divisors
    ├─ dc2 / dar   newer AIG-manager versions of similar ideas
    └─ mfs / sfm   SAT + don't-cares for tougher rewrites
```

Recipes like `resyn2` just **sequence** these.

---

## 1. Balance (`b` / `&b`)

**Idea:** multi-input AND trees are associative. Re-pair leaves to reduce levels,
while preferring pairs that already exist in the hash table (sharing).

| | Classic | GIA |
|--|---------|-----|
| Driver | `src/base/abci/abcBalance.c` | `src/aig/gia/giaBalAig.c` |
| Command | `balance` | `&b` |

**Watch:** `lev` in `ps` should drop; `and` may stay similar or improve via sharing.

---

## 2. Rewrite (`rw` / DAR)

**Idea:** for each node, take **4-input cuts**, compute the truth table, map it to
an **NPN class**, try precomputed replacement circuits, keep the best **gain**.

```
gain ≈ (nodes freed in MFFC) − (new nodes that are not already hashed)
accept if gain > 0   (or gain ≥ 0 with -z)
```

| Piece | Location |
|-------|----------|
| CLI / driver | `src/base/abci/abcRewrite.c` |
| Engine | `src/opt/rwr/rwrEva.c` (`Rwr_NodeRewrite`) |
| NPN / subgraphs | `src/opt/rwr/` + `src/bool/lucky/` |
| Newer twin | `src/opt/dar/` (`dc2` flow) |

**Flags to know:**
- `-z` — allow zero-cost replacements (often enables later gains)
- `-l` — level-aware / preserve delay style options (see `help rewrite`)

---

## 3. Refactor (`rf`)

**Idea:** pick a reconvergence-driven **cone**, collapse to a truth table,
re-factor (e.g. ISOP), replace if node count improves.

| Piece | Location |
|-------|----------|
| Driver | `src/base/abci/abcRefactor.c`, `abcReconv.c` |

Heavier than rewrite; used less frequently in recipes (`resyn2` uses it carefully).

---

## 4. Resubstitution (`rs`)

**Idea:** try to rebuild a node’s function from **nearby divisor nodes**
(constants, single divisors, OR/AND of a few divisors, …).

| Piece | Location |
|-------|----------|
| Driver | `src/base/abci/abcResub.c` |
| Windowed variants | `src/opt/res/` |

Typical knobs: `-K` (cut/support related), `-N` (max nodes added).

`resyn3` and `*rs` aliases in `abc.rc` emphasize resub heavily.

---

## 5. Don’t-care / SAT-based opts (`mfs`, …)

**Idea:** a node’s function only matters on **care** minterms (don’t-cares elsewhere).
Use SAT to find a simpler implementation valid on cares.

| Package | Role |
|---------|------|
| `src/opt/mfs/` | don’t-care optimization |
| `src/opt/sfm/` | SAT-based mapping/opt variants |

Slower, stronger — used when rewrite/refactor plateau.

---

## 6. Standard recipes (from `abc.rc`)

| Alias | Intent |
|-------|--------|
| `resyn` | light rewrite loop |
| `resyn2` | workhorse classic script |
| `resyn2a` | rewrite-heavy without refactor |
| `resyn3` | resub-centric |
| `compress` / `compress2` | level-aware (`-l`) versions |
| `choice` / `choice2` | store multiple versions → structural choices for mapping |
| `&dc3` / `&dc4` | GIA “lazy” synthesis snippets |

Always expand with `alias` inside ABC to see the live definition.

---

## 7. How to study one pass properly

For **rewrite** (recommended first algorithm deep-dive):

1. Run before/after `ps` on `i10.aig`
2. Read driver `abcRewrite.c` top-down (loop over nodes)
3. Enter `Rwr_NodeRewrite`
4. Note constants: cut size, max cuts kept, fanout skip, gain test
5. Only then open NPN table generation code

Same method works for any pass: **shell → wrapper → driver → innermost gain test**.

---

## 8. What “quality” means here

| Metric | Command | Better means |
|--------|---------|--------------|
| Area proxy | `and` / node count | lower |
| Delay proxy | `lev` | lower |
| After mapping | LUT count / levels | lower |

Tech-independent opts improve AIG metrics; mapping may trade them differently.

---

## Next

[06_MAPPING_AND_PROOF.md](06_MAPPING_AND_PROOF.md) — binding to LUTs/cells and proving equivalence.
