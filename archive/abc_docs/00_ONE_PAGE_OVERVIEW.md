# 00 — One-Page Overview: What Is ABC?

## In one sentence

**ABC** turns a Boolean circuit (gates / LUTs / AIG) into a **smaller / faster /
mapped** circuit, and can also **prove** two circuits are equivalent.

## Where it sits in EDA

```
RTL (Verilog) ──► synthesis frontend ──► gate/AIG netlist
                                              │
                                              ▼
                                    ┌─────────────────┐
                                    │      ABC        │
                                    │  logic opt +    │
                                    │  tech mapping   │
                                    │  + verification │
                                    └────────┬────────┘
                                             │
                     mapped LUTs / cells / AIG / BLIF / AIGER
                                             │
                                             ▼
                              place & route (e.g. OpenROAD)
```

ABC is **logic-level** EDA: it does not place transistors on a chip. OpenROAD
and similar tools sit *after* (or beside) ABC for physical design.

## What problems it solves

| Problem | Typical ABC answer |
|---------|-------------------|
| Circuit too many gates / deep levels | `resyn2`, `&syn2`, `rewrite`, `balance` |
| Need FPGA LUTs (K-input) | `if -K 6`, `&if -K 6` |
| Need standard cells | `map`, `amap`, Liberty (`scl`) |
| Are two designs the same? | `cec`, `&cec`, `fraig` |
| Sequential property / reachability | `pdr`, BMC packages under `sat/bmc` |

## Mental model (keep this)

ABC is a **command shell** around **graph data structures**:

1. You **read** a design into memory.
2. You run **commands** that rewrite that graph.
3. You **write** the result out (or verify it).

There is always a **current design** held by a global object called the **frame**
(`Abc_Frame_t`).

## Two representations (do not skip this)

| Name | Struct | Commands | Use when |
|------|--------|----------|----------|
| Classic network | `Abc_Ntk_t` | `rewrite`, `resyn2`, `if` | Learning, smaller designs, scripts in `abc.rc` |
| GIA (ABC9) | `Gia_Man_t` | `&syn2`, `&if`, `&b` | Large designs, modern/scalable path |

Same process, two graphs. Convert with:

```
&get   # classic → GIA
&put   # GIA → classic
```

## Core idea behind almost every optimizer

1. Look at a **local piece** of the graph (a node + small cut/cone).
2. Try a **functionally equivalent** replacement that uses fewer nodes or less depth.
3. Accept if the **gain** is good enough (greedy).
4. Repeat over all nodes, often in a fixed recipe (`resyn2`).

That is the whole game: local rewrites + structural hashing + recipes.

## What you can ignore at first

- Entire `src/sat/` solver internals (call them, don't study them yet)
- Entire `src/bdd/cudd/` (legacy BDD engine)
- `src/phys/` (tiny / rarely central)
- Most of `src/proof/` except `cec` / `fra` / `dch` once you need verification

## Next

Read [01_END_TO_END_FLOW.md](01_END_TO_END_FLOW.md) — the synthesis story as a pipeline.
