# 01 — End-to-End Flow (the synthesis story)

Read this as a movie plot. Every later doc zooms into one scene.

---

## Scene 0 — Boot

```
main()  →  Abc_RealMain()  →  Abc_FrameGetGlobalFrame()
                              │
                              ├─ register all packages/commands
                              ├─ source abc.rc  (aliases like resyn2)
                              └─ enter REPL  or  run -c "..."
```

**Files:** `src/base/main/main.c`, `mainReal.c`, `mainInit.c`, `abc.rc`

The frame owns:
- command + alias tables
- current classic network (`pNtkCur`)
- current GIA (`pGia`)
- libraries (LUT, Liberty, genlib, …)

---

## Scene 1 — Read a design

```
read / read_blif / read_aiger / read_verilog  →  Abc_Ntk_t in pNtkCur
```

**Package:** `src/base/io/`

Supported common formats: BLIF, AIGER (`.aig`), BENCH, PLA, structural Verilog.

After read you often see mixed gate types. Optimization wants a **uniform** form.

---

## Scene 2 — Normalize to AIG (`strash`)

```
strash   (alias: st)
```

Converts the network into a **structurally hashed AIG**:
- only 2-input AND nodes
- inversions = **complemented edges** (a bit, not a NOT gate)
- identical ANDs are merged via a hash table

**Why:** every later local rewrite assumes this canonical-ish form.

**Files:** `src/base/abc/abcAig.c` (+ conversion in IO / abci drivers)

---

## Scene 3 — Tech-independent optimization

Typical classic recipe (`abc.rc`):

```
resyn2 = b; rw; rf; b; rw; rwz; b; rfz; rwz; b
```

| Step | Alias | Meaning |
|------|-------|---------|
| `b` | balance | rebalance AND trees for depth / sharing |
| `rw` | rewrite | replace 4-input cuts with better subgraphs |
| `rf` | refactor | collapse a cone, re-factor if smaller |
| `rwz` / `rfz` | … `-z` | also accept **zero-cost** changes (can unlock later gains) |

Modern GIA twin:

```
&get; &syn2; &ps
```

**Packages:** `src/opt/rwr`, `src/opt/dar`, `src/base/abci/abcBalance.c`, …
GIA scripts: `src/aig/gia/giaScript.c`

Goal metrics you watch with `ps` / `&ps`:
- **and** = node count
- **lev** = logic levels (depth)

---

## Scene 4 — Technology mapping

After optimization, bind logic to a technology:

### FPGA (LUTs)

```
if -K 6          # classic priority-cut mapper
&if -K 6         # GIA version
```

**Package:** `src/map/if/`

### Standard cells

```
read_library something.genlib
map              # or amap
```

**Packages:** `src/map/mapper`, `src/map/amap`, `src/map/mio`

### Timing / Liberty

```
read_liberty ...
# scl package flows
```

**Package:** `src/map/scl/`

---

## Scene 5 — Verify (optional but important)

```
cec file1.blif file2.blif     # combinational equivalence
&cec
fraig                         # functional reduction via SAT
pdr                           # property directed reachability (sequential)
```

**Packages:** `src/proof/cec`, `src/proof/fra`, `src/proof/pdr`, SAT under `src/sat/`

Pattern: build a **miter** (XOR outputs of two circuits) → ask SAT if miter can be 1.

---

## Scene 6 — Write result

```
write_blif out.blif
write_aiger out.aig
write_verilog out.v
```

**Package:** `src/base/io/`

---

## Full classic example (one line)

```bash
./abc -c "read i10.aig; strash; resyn2; if -K 6; print_stats; write_blif out.blif"
```

Flow:

```
i10.aig ─read─► Ntk ─strash─► AIG ─resyn2─► smaller AIG ─if -K 6─► LUT netlist ─write─► out.blif
```

## Full modern (GIA) example

```bash
./abc -c "read i10.aig; &get; &syn2; &if -K 6; &ps; &put; write_blif out.blif"
```

---

## How OpenROAD relates (your repo context)

In a full ASIC flow:

1. Yosys / other frontend → logic netlist
2. **ABC** (often called from Yosys) → optimize + map
3. **OpenROAD** → floorplan, place, CTS, route, …

Your workspace has both `abc/` and `OpenROAD/` so you can study the logic layer
and the physical layer separately. ABC knowledge transfers directly to Yosys’s
`abc` pass scripts.

---

## Data movement summary

```
File on disk
    │  IO package
    ▼
Abc_Ntk_t  ◄──►  Gia_Man_t     (&get / &put)
    │                │
    │   opt/, map/   │   gia*, &commands
    ▼                ▼
optimized / mapped network
    │  IO package
    ▼
File on disk
```

---

## Next

Skim [02_DIRECTORY_MAP.md](02_DIRECTORY_MAP.md) so you know which folders exist
and which to open first.
