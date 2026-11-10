# 06 — Mapping and Proof

After tech-independent optimization you either **map** to a technology or **verify**.

---

## A. Technology mapping

### A1. FPGA LUT mapping — `if` / `&if`

**Goal:** cover the AIG with K-input LUTs, minimizing delay and/or area.

**Package:** `src/map/if/`  
**Key files:** `if.h`, `ifCore.c`, `ifMap.c`, `ifCut.c`

**Algorithm sketch (priority cuts):**

```
for each node in topological order:
    enumerate K-feasible cuts
    keep best ≤ nCutsMax cuts by a ranking function
choose a global cover (delay pass, then area recovery passes)
```

| Command | World |
|---------|-------|
| `if -K 6` | classic |
| `&if -K 6` | GIA |

Ranking typically considers delay, area flow, edge count, etc. (lexicographic
comparators in `ifCut.c` / related).

**Related:** `lutpack` (`lp`) for packing tweaks after mapping.

---

### A2. Standard-cell mapping

```
read_library my.genlib     # mio package
map                        # or amap
```

| Package | Role |
|---------|------|
| `src/map/mio/` | genlib parsing |
| `src/map/mapper/` | classic mapper |
| `src/map/amap/` | another std-cell mapper |
| `src/map/super/` | supergate libraries |

---

### A3. Liberty / timing (`scl`)

```
read_liberty tech.lib
# then scl sizing / buffering style flows
```

**Package:** `src/map/scl/`

Used when delay is characterized by real cell libraries, not just unit AIG levels.

---

### A4. Structural choices (better mapping)

Scripts `choice` / `choice2` in `abc.rc`:

1. Optimize along different recipes  
2. `fraig_store` snapshots  
3. `fraig_restore` merges **functionally equivalent alternatives**  
4. Mapper picks among choices

**Engine:** `src/proof/dch/` (and fraig store machinery on the frame’s `vStore`)

---

## B. Verification and proof

### B1. Combinational equivalence — `cec`

```
cec gold.blif gate.blif
# or operate on current vs file / two networks depending on usage
```

**Idea:** miter the outputs → SAT/sweeping → equivalent or counterexample.

**Package:** `src/proof/cec/`

GIA: `&cec`.

---

### B2. FRAIG — `fraig`

**Functional Reduction of AIGs:** merge nodes that are functionally equivalent
(using simulation + SAT), not merely structurally identical.

**Packages:** `src/proof/fra/`, `src/proof/fraig/`

Used both as a sweeper and inside choice construction.

---

### B3. Sequential proving — `pdr` / BMC

| Tool | Package | Use |
|------|---------|-----|
| PDR / IC3 style | `src/proof/pdr/` | safety properties / unreachable bad states |
| BMC | `src/sat/bmc/` | bounded time-frame unrolling + SAT |

Sequential AIGs involve registers (`nRegs` in GIA, latches in classic nets).

---

### B4. How SAT plugs in (conceptual)

```
proof / mfs / fraig / cec / pdr
        │
        ▼
   CNF construction   (src/sat/cnf/ …)
        │
        ▼
   SAT solver         (bsat, glucose, kissat, …)
        │
        ▼
   sat / unsat / cex
```

You rarely need solver internals to understand ABC’s *synthesis* story.

---

## C. Minimal verify loop (practice)

```bash
./abc -c "read i10.aig; strash; write_aiger before.aig; resyn2; write_aiger after.aig; cec before.aig after.aig"
```

Expect equivalence if optimization is correct — a great sanity check when you
modify a pass.

---

## Next

[07_HANDS_ON.md](07_HANDS_ON.md) — build and run guided sessions.
