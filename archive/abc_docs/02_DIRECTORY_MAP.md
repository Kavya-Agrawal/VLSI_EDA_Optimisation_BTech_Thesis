# 02 — Directory Map (read vs skip)

Root: `hardware_eda/abc/`

Rough size: **~2300 files**. Treat folders as **packages** (each has a role).

---

## Top level

| Path | Role |
|------|------|
| `abc.rc` | ★ Aliases & recipes (`resyn2`, `compress2`, …). Read early. |
| `Makefile` / `CMakeLists.txt` | Build system |
| `src/` | All C/C++ sources |
| `src/demo.c` | How to link ABC as a library |
| `i10.aig` | Tiny sample circuit |
| `README.md` | Build / bug-report notes |

---

## `src/` packages at a glance

```
src/
├── base/     ★ framework + classic network + commands + IO     START HERE
├── aig/      ★ GIA and other AIG managers                      START HERE (after base)
├── opt/      ★ tech-independent optimization                   CORE ALGORITHMS
├── map/      ★ technology mapping                              CORE ALGORITHMS
├── proof/    equivalence checking / sequential proof           later
├── sat/      SAT solvers + BMC                                 call sites only at first
├── bool/     truth tables, NPN, decomposition                  when reading rewrite
├── bdd/      CUDD BDDs                                         skip at first
├── misc/     vec/, util, hash, timing helpers                  learn vec/ early
└── phys/     placement stub                                    skip
```

---

## `src/base/` — the skeleton (must learn)

| Subdir | What it is | First files |
|--------|------------|-------------|
| `main/` | Entry, frame, init | `mainReal.c`, `mainInt.h`, `abcapis.h` |
| `cmd/` | Command table, aliases, execute | `cmdApi.c` |
| `abc/` | `Abc_Ntk_t` / `Abc_Obj_t`, strashing | `abc.h`, `abcAig.c` |
| `abci/` | Command wrappers + drivers | `abc.c` (dispatch), `abcRewrite.c`, … |
| `io/` | Read/write formats | skim headers; dive when parsing fails |
| `wlc/`, `wln/`, `cba/`, `bac/` | Word-level / hierarchical frontends | later |
| `pla/`, `ver/`, `exor/` | PLA / Verilog helpers / EXOR | as needed |

**How to find any command:** grep the command string in `src/base/abci/abc.c`
(look for `Cmd_CommandAdd`).

---

## `src/aig/` — graph managers

| Subdir | Struct | Notes |
|--------|--------|-------|
| `gia/` | `Gia_Man_t` | ★ Modern scalable AIG — learn this well |
| `aig/` | `Aig_Man_t` | Mid-era; used by DAR (`dc2`), DCH, … |
| `saig/` | sequential AIG helpers | sequential flows |
| `hop/` | local AIGs | used inside some opts |
| `ivy/`, `miniaig/`, `ioa/` | older / specialized | lower priority |

---

## `src/opt/` — optimizers (the “brain”)

| Subdir | Commands / role |
|--------|-----------------|
| `rwr/` | classic `rewrite` (NPN + subgraphs) |
| `dar/` | newer rewrite/refactor/balance (`dc2` path) |
| `res/` | window resubstitution |
| `mfs/` | don't-care SAT optimization |
| `cut/` | cut enumeration utilities |
| `sfm/`, `sbd/`, `fxu/`, … | more specialized restructuring |
| `sim/`, `fsim/` | simulation support |

**First dive:** `rwr/` after you can run `rw` from the shell.

---

## `src/map/` — technology mapping

| Subdir | Role |
|--------|------|
| `if/` | ★ FPGA priority-cut LUT mapper (`if`, `&if`) |
| `mapper/`, `amap/` | standard-cell mappers |
| `mio/` | genlib library reader |
| `scl/` | Liberty timing / gate sizing |
| `mpm/`, `fpga/`, `super/`, … | other mappers / supergates |

---

## `src/proof/` — verification

| Subdir | Role |
|--------|------|
| `cec/` | combinational equivalence |
| `fra/`, `fraig/` | FRAIG / functional reduction |
| `dch/` | structural choices for mapping |
| `pdr/` | PDR / IC3-style sequential proving |
| `ssw/`, `abs/`, … | sequential sweep / abstraction |

---

## `src/sat/` — solvers (treat as black boxes first)

Many solvers live here (`bsat`, `glucose`, `kissat`, `satoko`, `cadical`, …)
plus `bmc/` and `cnf/`.

**Your job early on:** know *that* ABC calls SAT for FRAIG/CEC/MFS/PDR — not
*how* CDCL works inside each solver.

---

## `src/bool/` and `src/misc/`

| Path | Learn because |
|------|----------------|
| `bool/kit/` | truth-table operations |
| `bool/lucky/` | NPN canonization (rewrite) |
| `misc/vec/` | ★ `Vec_Int_t`, `Vec_Ptr_t` everywhere |
| `misc/st/`, `misc/hash/` | hash tables |
| `misc/util/` | portable helpers |

---

## Recommended exploration order

```
Week sense of the tree:
  base/main → base/cmd → base/abc → abc.rc
       → one abci driver (rewrite)
       → opt/rwr
       → aig/gia
       → map/if
       → proof/cec (lightly)
```

---

## Next

[03_DATA_STRUCTURES.md](03_DATA_STRUCTURES.md) — the objects those folders manipulate.
