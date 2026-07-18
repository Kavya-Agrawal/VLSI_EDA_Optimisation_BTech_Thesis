# 01 — Understanding the ABC Codebase (read, build, use, play)

> Target: go from "60k-line C project, where do I even start?" to
> "I can trace `resyn2` end-to-end and modify a pass."
> All paths are relative to your clone at `hardware_eda/abc`.

---

## 1. The 30-second mental model

ABC is a **REPL (command shell) around graph data structures for Boolean logic**.

```
 main() → Abc_RealMain()                      src/base/main/main.c, mainReal.c
   │
   Abc_FrameGetGlobalFrame()   ← singleton "the frame" (Abc_Frame_t)
   │        holds: command table, aliases, AND the current design(s)
   │
   Cmd_CommandExecute("b; rw; rf")            src/base/cmd/cmdApi.c
   │        split on ';' → expand aliases (abc.rc) → dispatch to C function
   │
   ┌────────────────┴───────────────────┐
   ▼                                    ▼
 pNtkCur : Abc_Ntk_t                 pGia : Gia_Man_t
 "classic world"                     "ABC9 / & world"
 rewrite, refactor, resub,           &syn2, &if, &b, &fraig, &ps
 balance, if, map, mfs               (modern, scalable, cache-friendly)
         └────────── &get / &put ──────────┘
```

Two parallel design representations live in the same process:

| | Classic (`Abc_Ntk_t`) | ABC9 / GIA (`Gia_Man_t`) |
|---|---|---|
| Commands | `rewrite`, `resyn2`, `if`, `ps` | `&syn2`, `&if`, `&b`, `&ps` |
| Storage | object structs + fanin/fanout int vectors | one dense array, fanins = integer *offsets* |
| Scale | ok up to ~1M nodes | industrial (many-million node) designs |
| Where held | `pAbc->pNtkCur` | `pAbc->pGia` |
| Bridge | `&get` (Ntk→Gia), `&put` (Gia→Ntk) | |

---

## 2. Directory map (what to read, what to skip)

```
abc/
├── abc.rc                  ★ startup aliases — resyn2 lives HERE, read this first
├── src/
│   ├── base/               ★ framework: THE place to start reading
│   │   ├── main/           entry point, Abc_Frame_t (mainInt.h), package init
│   │   ├── cmd/            command table, alias expansion, dispatch
│   │   ├── abc/            Abc_Ntk_t / Abc_Obj_t structs + strashing (abcAig.c)
│   │   ├── abci/           ★ abc.c (~60k lines): every command's CLI wrapper
│   │   └── io/             read/write BLIF, AIGER, Verilog, BENCH...
│   ├── aig/
│   │   ├── gia/            ★ modern scalable AIG (Gia_Man_t) — the future of ABC
│   │   ├── aig/            mid-era Aig_Man_t (used by dar rewriting, dch...)
│   │   └── hop/, saig/     local AIGs, sequential AIG
│   ├── opt/                ★ tech-independent optimization (the interesting algorithms)
│   │   ├── rwr/            rewrite: NPN classes + precomputed subgraphs
│   │   ├── dar/            newer rewrite/refactor/balance over Aig_Man_t (dc2)
│   │   ├── mfs/            don't-care optimization with SAT
│   │   ├── res/            window-based resubstitution
│   │   └── cut/            cut enumeration
│   ├── map/                ★ technology mapping
│   │   ├── if/             FPGA LUT mapper (priority cuts) — most studied for ML
│   │   ├── mapper/, amap/  standard-cell mappers
│   │   ├── scl/            Liberty timing/sizing
│   │   └── mio/            genlib library reader
│   ├── proof/              equivalence checking: cec/, fra/ (fraig), dch/ (choices), pdr/
│   ├── sat/                SAT solvers: bsat/ (MiniSat-style), glucose, kissat, bmc/
│   ├── bool/               truth-table kit (kit/), bi-decomposition (bdc/), NPN (lucky/)
│   ├── bdd/                CUDD BDD package
│   └── misc/               vec/ (THE vector types), st/ (hash), util, tim (timing)
```

**Skip on first pass:** `bdd/` (legacy), `phys/`, most of `proof/` except `dch`/`fra`, `sat/` internals.

---

## 3. The core data structures (need-to-know only)

### 3.1 Classic network — `src/base/abc/abc.h`

- `Abc_Ntk_t` = the network: vectors of all objects, PIs/POs, a functionality
  manager, name manager. Network *types*: NETLIST / LOGIC / **STRASH** (an AIG of
  2-input ANDs with complemented edges — this is what `strash` produces and what
  `rewrite`/`resyn2` require).
- `Abc_Obj_t` = one node/PI/PO/latch. Fanins/fanouts are **vectors of integer IDs**
  resolved through `pNtk->vObjs`.
- **Complemented edges**: inversion is a *bit*, not a node. Two encodings:
  - stored bits `fCompl0/fCompl1` on the object, and
  - **pointer tagging** — the LSB of an `Abc_Obj_t*` marks complement:
    `Abc_ObjNot(p)` just XORs the pointer with 1. You'll see this everywhere.
- **Structural hashing** (`src/base/abc/abcAig.c`): `Abc_AigAnd(a,b)` looks up a hash
  table of (fanin0, fanin1, compl bits); an identical AND is never created twice.
  This keeps the AIG canonical-ish and is why "rewriting" can *reuse* existing logic.

### 3.2 GIA — `src/aig/gia/gia.h` (the one to learn well)

```c
struct Gia_Obj_t_ {           // ~16 bytes, lives in ONE big array
    unsigned iDiff0 : 29;     // fanin0 = (this node's index) - iDiff0
    unsigned fCompl0: 1;      // fanin0 complemented?
    ...
    unsigned iDiff1 : 29;     // fanin1 as an offset too
    unsigned fCompl1: 1;
    unsigned Value;           // scratch: algorithms stash per-node data here
};
```

- Fanins are *relative offsets* into the array → cache-friendly, tiny, scalable.
- APIs talk in **literals**: `lit = 2*var + complement` (`Abc_Var2Lit`). 
  `Gia_ManHashAnd(p, lit0, lit1)` returns the literal of the (possibly reused) AND.
- Fanouts are OPTIONAL (computed on demand) — most passes work with levels+refs.

### 3.3 The frame — `src/base/main/mainInt.h`

`Abc_Frame_t` holds `pNtkCur`, `pGia`, backup chains (undo), loaded libraries
(`pLibLut`, `pLibScl`...), and the command/alias hash tables. Every command
receives `Abc_Frame_t *pAbc` as its first argument.

---

## 4. How a command actually runs (trace `rewrite` once)

1. You type `rw`. `Cmd_CommandExecute` splits on `;`, expands alias `rw` → `rewrite`
   (aliases loaded from `abc.rc` at startup).
2. Dispatch looks up `"rewrite"` in `pAbc->tCommands` → `Abc_CommandRewrite`
   in `src/base/abci/abc.c` (the giant file: every command has a `Abc_CommandXxx`
   wrapper there that parses flags and calls the real engine).
3. `Abc_CommandRewrite` → `Abc_NtkRewrite` in `src/base/abci/abcRewrite.c`.
4. `Abc_NtkRewrite` iterates nodes, calls `Rwr_NodeRewrite` (`src/opt/rwr/rwrEva.c`)
   per node: enumerate 4-input cuts → NPN-canonize truth table → look up
   precomputed replacement subgraphs → pick best gain → replace if gain > 0.

That wrapper→engine pattern (`abc.c` wrapper → `abci/abcXxx.c` driver → `opt/xxx/`
engine) repeats for every command. **To find any command's implementation:**
grep for `"commandname"` inside `src/base/abci/abc.c`, find the `Cmd_CommandAdd`
line, and follow the function pointer.

### What `resyn2` really is

`abc.rc` line ~111: 

```
alias resyn2 "b; rw; rf; b; rw; rwz; b; rfz; rwz; b"
```

i.e. balance → rewrite → refactor → balance → rewrite → rewrite-zero-cost →
balance → refactor-zero → rewrite-zero → balance. It's just a **fixed recipe of
greedy passes** — this fixedness is exactly what DRiLLS/ABC-RL attack with RL.

`&syn2` is *not* the same: `Gia_ManAigSyn2` (`src/aig/gia/giaScript.c`) is a
GIA-native flow (area balance + cut-mapping-based restructuring iterations).

---

## 5. Building ABC

### Windows (your machine)
The official route is MSVC (the Unix Makefile is not the CI path on Windows):
- CI recipe: `.github/workflows/build-windows.yml` — builds `abcspace.sln` /
  `abcexe.vcxproj` with `msbuild ... /p:Platform=Win32`, linking pthreads-win32.
- **Far easier: use WSL2** (Ubuntu) and build the Linux way. All ML-for-EDA
  tooling (PyTorch, abc_py) assumes Linux; WSL2 is strongly recommended for the BTP.

### Linux / WSL2
```bash
sudo apt install build-essential libreadline-dev
cd abc
make -j$(nproc) abc          # the ./abc binary
make libabc.a                # static library (for embedding)
make ABC_USE_PIC=1 libabc.so # shared library (for Python ctypes/pybind11)
```
Useful flags: `ABC_USE_NO_READLINE=1`, `ABC_USE_NO_PTHREADS=1`,
`ABC_USE_NAMESPACE=xxx` (compile as C++ in a namespace).
The Makefile auto-includes any `src/ext*` directory — the sanctioned way to add
your own module without touching upstream files.

---

## 6. Playing with ABC — hands-on session

```bash
./abc
# inside the shell:
abc 01> read i10.aig            # or read_blif / read_verilog (structural only)
abc 02> ps                      # print_stats: i/o, nodes, levels
abc 03> strash                  # convert to structurally-hashed AIG
abc 04> resyn2; ps              # classic optimization recipe
abc 05> if -K 6; ps             # map to 6-input LUTs
abc 06> write_blif out.blif

# the ABC9 world:
abc 07> &get                    # copy current network into the GIA space
abc 08> &ps                     # GIA stats
abc 09> &syn2; &ps              # modern synthesis
abc 10> &if -K 6; &ps           # GIA LUT mapping
abc 11> &put                    # bring result back to the classic world
```

Batch mode (what RL frameworks use):
```bash
./abc -c "read i10.aig; strash; resyn2; if -K 6; print_stats"
```

Good starter experiments:
1. Run `resyn2` 1×, 2×, 5× on an EPFL benchmark and watch diminishing returns (`ps` after each).
2. Compare `rw` vs `rwz` vs `rf` gains per pass on different circuits — you'll see
   *why* recipe choice matters per-circuit (the DRiLLS premise).
3. `source abc.rc` then `alias` to list all script definitions.
4. Time `&syn2` vs `resyn2` on a big AIGER file — feel the GIA speed difference.

**Benchmarks to get:** EPFL combinational suite (github.com/lsils/benchmarks),
ISCAS'85/89, and the MCNC set. All read directly as `.aig`/`.blif`.

---

## 7. Reading strategy for the source (2-week plan)

| Day | Read | Goal |
|-----|------|------|
| 1–2 | `abc.rc`, `src/base/main/mainReal.c`, `mainInt.h` | REPL + frame model |
| 3–4 | `src/base/abc/abc.h` (structs, inlines), `abcAig.c` | classic AIG + strashing |
| 5–6 | `src/base/abci/abcRewrite.c` + `src/opt/rwr/rwrEva.c` | one full pass end-to-end |
| 7 | `src/base/abci/abcBalance.c`, `abcRefactor.c`, `abcResub.c` | the rest of resyn2 |
| 8–9 | `src/aig/gia/gia.h`, `giaHash.c`, `giaScript.c` | GIA world |
| 10–11 | `src/map/if/if.h`, `ifCore.c`, `ifMap.c`, `ifCut.c` | priority-cut mapping |
| 12 | `src/opt/mfs/`, `src/proof/dch/dchCore.c` | SAT-based opt + choices |
| 13–14 | `src/demo.c`, `src/base/main/abcapis.h` | embedding API (for ML integration) |

Tips:
- Every file has a uniform header comment with `Synopsis`; grep those for orientation.
- `Vec_Int_t`, `Vec_Ptr_t` (`src/misc/vec/`) are used everywhere — learn their 10
  macros (`Vec_IntForEachEntry`, ...) once and all code becomes readable.
- Per-node scratch state is stashed in `pObj->Value` (GIA) or `pObj->pCopy`
  (classic) — when confused about "where data flows", look for these.
- The `Abc_NtkForEachNode` / `Gia_ManForEachAnd` iteration macros define the
  processing order — that order itself is a heuristic (see `02_HEURISTIC_MAP.md`).
