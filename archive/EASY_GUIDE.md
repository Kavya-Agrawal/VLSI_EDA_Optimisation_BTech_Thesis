# The Easy Guide — ABC + OpenROAD in Plain English

> **What this file is:** a single, complete, easy-to-read summary of your two big
> documentation sources — the **ABC learning pack** (`abc_docs/`) and the
> **OpenROAD documentation** (theopenroadproject.org). It pulls out everything
> important so you don't have to read thousands of pages. Read this first; open
> the deep docs only when you want more detail.
>
> **The one-line mental model of the whole thing:**
> `Verilog (RTL) → [ABC: make the logic small & map it] → [OpenROAD: place it on the chip & wire it] → GDSII (a real chip layout)`

---

## PART 0 — How to actually learn this (your reading flow)

Don't read top-to-bottom randomly. Follow this order. Each step builds on the last.

```
STEP 1  Understand the big picture         →  PART 1 here            (5 min)
STEP 2  Understand ABC (logic level)       →  PART 2 here            (30 min)
STEP 3  Understand OpenROAD (physical)     →  PART 3 here            (20 min)
STEP 4  See how they connect               →  PART 4 here            (5 min)
STEP 5  Keep the cheat sheets handy         →  PART 5 here            (reference)
STEP 6  ONLY IF you want depth:
          - ABC internals   → abc_docs/00 … 08 (in order)
          - Hands-on runs   → abc_docs/07_HANDS_ON.md
          - OpenROAD hands-on → theopenroadproject.org docs
```

**The single golden rule for both tools:** they are just a **shell** (you type
commands) that **transforms a graph/design** in memory, step by step, and then
**writes a file out**. Read → transform → write. That's it.

---

## PART 1 — The Big Picture (where everything sits)

Making a chip goes from "code" to "physical layout" in two big halves:

```
        YOU WRITE                    LOGIC HALF                 PHYSICAL HALF
   ┌──────────────────┐      ┌────────────────────────┐   ┌────────────────────────┐
   │  RTL in Verilog  │ ───► │   ABC  (via Yosys)      │──►│   OpenROAD              │
   │ (how it behaves) │      │  make logic small +     │   │  arrange on silicon +   │
   └──────────────────┘      │  map to gates/LUTs +    │   │  wire everything +      │
                             │  prove it's still equal │   │  check timing           │
                             └────────────────────────┘   └────────────────────────┘
                                        │                            │
                                   gate netlist                   GDSII file
                                                                (sent to factory)
```

| Half | Tool | Question it answers | Works on |
|------|------|---------------------|----------|
| **Logic** | **ABC** | "What is the *smallest/fastest* set of gates that does this logic?" | Boolean logic (gates, AIG, LUTs) |
| **Physical** | **OpenROAD** | "*Where* on the chip does each gate go, and *how* are they wired?" | Real geometry (x/y coordinates, metal wires) |

ABC does **not** place anything on silicon. OpenROAD does **not** rethink your
logic. They are two different jobs, done one after the other.

---

## PART 2 — ABC in Plain English

**ABC = "A System for Sequential Logic Synthesis and Verification."**
It's a huge C codebase (~2,300 files), but you only need a handful of ideas.

### 2.1 What ABC does (one sentence)
It turns a Boolean circuit into a **smaller / faster / technology-mapped**
circuit, and can also **prove** two circuits are equivalent.

### 2.2 The mental model (keep this forever)
ABC is a **command shell wrapped around graph data structures**:

1. You **read** a design into memory.
2. You run **commands** that rewrite that graph (make it smaller/faster).
3. You **write** the result out — or **verify** it.

There is always **one "current design"** held by a global object called the
**frame** (`Abc_Frame_t`). Think of it as ABC's short-term memory.

### 2.3 The single picture that matters

```
                    ┌─────────────────────────────────────┐
                    │         Abc_Frame_t (global)        │  ← the "memory"
                    │  command table · aliases · libraries │
                    └──────────────┬──────────────────────┘
                                   │
              ┌────────────────────┴────────────────────┐
              ▼                                          ▼
       pNtkCur : Abc_Ntk_t                        pGia : Gia_Man_t
       "classic world"                            "ABC9 / & world"
       rewrite, resyn2, if, map                   &syn2, &if, &b, &fraig
              │                                          │
              └────────────── &get / &put ───────────────┘
                                   │
                                   ▼
                    read → strash → optimize → map → verify → write
```

### 2.4 Two representations (do NOT skip this)
Same tool, two ways to store the circuit graph:

| Name | Struct | Commands (examples) | Use when |
|------|--------|---------------------|----------|
| **Classic network** | `Abc_Ntk_t` | `rewrite`, `resyn2`, `if`, `map` | Learning, smaller designs, `abc.rc` scripts |
| **GIA (a.k.a. ABC9)** | `Gia_Man_t` | `&syn2`, `&if`, `&b`, `&fraig` | Large designs, modern scalable path |

Convert between them:
- `&get` → classic → GIA
- `&put` → GIA → classic

> Tip: `&`-prefixed commands work on GIA. If a normal command "does nothing,"
> you may be sitting in the wrong world — bridge with `&get`/`&put`.

### 2.5 The end-to-end flow (the "movie plot")

```
File on disk
   │  read / read_aiger / read_blif      (IO package)
   ▼
Abc_Ntk_t  ──strash──►  AIG (only 2-input ANDs + inversion-as-a-flag)
   │
   │  resyn2  (optimize: make it smaller & shallower)
   ▼
smaller AIG
   │  if -K 6   (map to FPGA 6-input LUTs)   OR   map (map to standard cells)
   ▼
mapped netlist
   │  cec / fraig   (optional: PROVE it still equals the original)
   ▼
   │  write_blif / write_aiger / write_verilog
   ▼
File on disk
```

**The 6 scenes:**

| Scene | Command | What happens |
|-------|---------|--------------|
| 0. Boot | `main()` | Loads commands + `abc.rc` script aliases, opens the prompt |
| 1. Read | `read i10.aig` | File → `Abc_Ntk_t` in memory. Formats: BLIF, AIGER, BENCH, PLA, Verilog |
| 2. Normalize | `strash` (`st`) | Convert to a clean **AIG**: only 2-input ANDs; inversions are just a bit on the edge; duplicate ANDs are merged (hashed) |
| 3. Optimize | `resyn2` | Repeatedly rewrite local pieces to use fewer gates / less depth |
| 4. Map | `if -K 6` or `map` | Bind logic to real hardware: FPGA LUTs or standard cells |
| 5. Verify | `cec`, `fraig`, `pdr` | Prove two circuits are equal (or find a counterexample) |
| 6. Write | `write_blif out.blif` | Netlist back to a file |

**Two full one-liners you can actually run:**
```bash
# Classic path
./abc -c "read i10.aig; strash; resyn2; if -K 6; print_stats; write_blif out.blif"

# Modern GIA path
./abc -c "read i10.aig; &get; &syn2; &if -K 6; &ps; &put; write_blif out.blif"
```

### 2.6 The optimization passes (what actually shrinks the circuit)
All are **greedy local search**: look at a small piece, try a smaller
equivalent replacement, keep it if it helps, repeat.

| Pass | Alias | Idea in one line |
|------|-------|------------------|
| **Balance** | `b` | Re-pair AND trees to reduce depth (levels) and share logic |
| **Rewrite** | `rw` | Replace small 4-input cuts with pre-computed better subgraphs |
| **Refactor** | `rf` | Collapse a cone of logic, re-factor it if the result is smaller |
| **Resub** | `rs` | Rebuild a node's function using nearby existing nodes ("divisors") |
| **Don't-care / SAT opt** | `mfs` | Use SAT + don't-cares for harder rewrites (slower, stronger) |

The `-z` suffix (e.g. `rwz`) means **"accept zero-cost changes too"** — no
immediate gain, but it can unlock gains in the *next* step.

**`resyn2` is not one algorithm — it's a fixed recipe (an alias):**
```
resyn2 = b; rw; rf; b; rw; rwz; b; rfz; rwz; b
```
That's why "which recipe / what order" is itself a research topic.

**Metrics you watch (with `ps` / `&ps`):**
- `and` = number of nodes ≈ **area** (lower is better)
- `lev` = number of logic levels ≈ **delay/depth** (lower is better)

### 2.7 Mapping + Proof (the last two jobs)

**Mapping = binding abstract logic to real hardware:**
- **FPGA LUTs:** `if -K 6` (classic) / `&if -K 6` (GIA) — cover the AIG with
  K-input lookup tables using "priority cuts."
- **Standard cells:** `read_library my.genlib; map` (or `amap`) — use real gates.
- **Timing (Liberty):** `read_liberty tech.lib` then `scl` flows for real cell delays.
- **Structural choices** (`choice`/`choice2`): keep several optimized versions and
  let the mapper pick the best — usually gives better results.

**Proof = making sure optimization didn't change behavior:**
- `cec` — **c**ombinational **e**quivalence **c**heck (are two circuits equal?)
- `fraig` — merge nodes that are *functionally* equal (via simulation + SAT)
- `pdr` — sequential proving (properties over time, with registers)
- **How it works underneath:** build a **miter** (XOR the outputs of the two
  circuits) → ask a **SAT solver** "can this output ever be 1?" → if no, they're equal.

> You call SAT solvers; you don't need to understand *how* they work inside.

### 2.8 ABC codebase survival rules (if you ever open the source)
1. **Never start in `sat/` or `bdd/`** — those are engines ABC *calls*, not the story.
2. **Always start from a command** — type it, then grep its name in `src/base/abci/abc.c`.
3. **Two worlds** — classic vs `&`-prefixed GIA. Bridge with `&get`/`&put`.
4. **Recipes live in `abc.rc`** — `resyn2` is just an alias chain, not magic C.
5. **Learn the `Vec_*` macros once** (`src/misc/vec/`) and half the code becomes readable.

**Where things live (cheat sheet):**

| I want… | Open this |
|---------|-----------|
| Entry / startup | `src/base/main/mainReal.c`, `mainInt.h` |
| Global state (the frame) | `src/base/main/mainInt.h` → `Abc_Frame_t` |
| Command dispatch | `src/base/cmd/` |
| Classic AIG network | `src/base/abc/abc.h`, `abcAig.c` |
| All command wrappers | `src/base/abci/abc.c` (huge file) |
| Modern scalable AIG | `src/aig/gia/gia.h` |
| Rewrite engine | `src/opt/rwr/` |
| FPGA LUT mapper | `src/map/if/` |
| Recipes / aliases | `abc.rc` |

**How any command runs (the pattern):**
```
you type "rw"
   → alias expands (rw → rewrite)                 (src/base/cmd/)
   → Abc_CommandRewrite()                          (src/base/abci/abc.c)
   → Abc_NtkRewrite()                              (abci/abcRewrite.c)
   → Rwr_NodeRewrite()  ← the actual algorithm     (src/opt/rwr/rwrEva.c)
```
CLI wrapper → driver → engine. Every feature follows this shape.

---

## PART 3 — OpenROAD in Plain English

**OpenROAD = a fully open-source, autonomous RTL-to-GDSII chip layout tool chain.**
It was started in 2018 under the DARPA IDEA program (led by UC San Diego, with
Qualcomm, Arm, and university partners). Its goal: remove the cost, expertise,
and unpredictability that block people from building real chips.
[[source]](https://theopenroadproject.org/welcome-to-openroads-documentation/)

### 3.1 Its big goals (why it exists)
- **No-Human-In-Loop (NHIL):** run the whole flow with little/no human help.
- **24-hour turnaround:** finish a design in a day.
- **No loss of PPA:** keep good **P**ower, **P**erformance, **A**rea quality.
- Uses **machine learning** to predict and auto-tune the flow, and **splits big
  problems into pieces** solved in parallel on the cloud.

### 3.2 Two things called "OpenROAD" (don't get confused)

| Release | What it is |
|---------|-----------|
| **The Application** | One standalone binary that does the *whole* RTL-to-GDSII job: synthesis → floorplan → … → detailed routing → metal fill → signoff timing/parasitics. |
| **The Flow** (OpenROAD-flow-scripts / ORFS) | A set of ready-made scripts that glue open-source tools together into a push-button RTL-to-GDSII flow. Best starting point for beginners. |

> **Beginner tip:** start with **the Flow (ORFS)** — you run one command and get a
> chip. Later, open **the Application** to control individual stages.

### 3.3 Where OpenROAD sits (recap)
It runs **after** logic synthesis. The typical full ASIC chain is:
```
Yosys (RTL → logic netlist)  →  ABC (optimize + map the logic)  →  OpenROAD (physical design)  →  GDSII
```
(Yosys actually calls ABC internally — so your ABC knowledge transfers directly.)

### 3.4 The physical-design flow (what OpenROAD does, stage by stage)
This is the "RTL-to-GDSII" pipeline. Read it as another movie plot:

```
gate netlist (from synthesis/ABC)
   │
   1. FLOORPLAN      decide chip size, rows, I/O pins, power grid (PDN)
   │
   2. PLACEMENT      global place (rough spots) → detailed place (legal, on-grid)
   │                 (macros like RAMs placed first)
   3. CTS            Clock Tree Synthesis: build a balanced clock network
   │                 so the clock reaches every flip-flop at ~the same time
   4. ROUTING        global route (plan wire paths) → detailed route (exact metal)
   │
   5. FINISHING      metal fill, cleanup
   │
   6. SIGNOFF        extract parasitics (RC) + static timing analysis (STA)
   │                 → confirm timing/power are met
   ▼
GDSII  (the geometry file the fab uses to make the chip)
```

### 3.5 The stages explained simply

| # | Stage | Plain-English job |
|---|-------|-------------------|
| 1 | **Floorplan** | Draw the empty chip: how big, where the rows go, where input/output pins sit, and lay down the **power grid** that feeds every cell. |
| 2 | **Placement** | Decide the **x,y position** of every gate. *Global placement* = rough, spread-out positions; *detailed placement* = snap them to legal grid spots without overlaps. Big blocks (**macros**, e.g. memories) are placed first. |
| 3 | **Clock Tree Synthesis (CTS)** | The clock signal must arrive everywhere at nearly the same time. CTS builds a tree of buffers to balance this (minimize "skew"). |
| 4 | **Routing** | Draw the actual metal wires connecting all pins. *Global routing* plans the rough paths; *detailed routing* lays exact wires on metal layers without shorts/spacing violations. |
| 5 | **Finishing** | Add **metal fill** (dummy metal for manufacturing uniformity) and clean up. |
| 6 | **Signoff** | **Parasitic extraction** measures the resistance/capacitance of the real wires; **Static Timing Analysis (STA)** then checks the chip actually meets its speed and power targets. |

### 3.6 The tools inside OpenROAD (names you'll see)
OpenROAD is modular — each stage is a tool. You don't need to memorize these, but
recognizing them helps:

| Stage | Tool / command prefix | Does |
|-------|----------------------|------|
| Floorplan init | `ifp` | Initialize floorplan (die/core area, rows) |
| Power grid | `pdn` | Build power distribution network |
| Macro placement | `mpl` | Place big blocks (memories, IP) |
| Global placement | `gpl` | Rough cell placement |
| Detailed placement | `dpl` | Legalize placement onto the grid |
| Resizing / buffering | `rsz` | Fix timing by sizing/buffering gates |
| Clock tree | `cts` (TritonCTS) | Balance the clock |
| Global routing | `grt` (FastRoute) | Plan wire routes |
| Detailed routing | `drt` (TritonRoute) | Lay exact metal |
| Parasitic extraction | `rcx` (OpenRCX) | Extract R/C of wires |
| Timing analysis | `sta` (OpenSTA) | Check timing |
| Metal fill | `fin` | Fill for manufacturing |

### 3.7 The metrics OpenROAD cares about (PPA)
- **Power** — how much energy the chip uses.
- **Performance** — how fast it can run (clock frequency; met via timing/STA).
- **Area** — how much silicon it takes (cost).
Every stage is trying to keep these good, just like ABC watches `and`/`lev`.

### 3.8 The OpenROAD ecosystem (from your repo folders)
Your workspace also has related projects:
- **ORAssistant** — an AI chatbot/assistant for answering OpenROAD questions.
- **OpenROAD-MCP** — an MCP server that lets AI agents drive OpenROAD.
- **MacroPlacement** — testcases and ML research for placing macros (memories) well.

### 3.9 Where to get OpenROAD help / links
[[docs home]](https://theopenroadproject.org/welcome-to-openroads-documentation/)
- Project + news: https://theopenroadproject.org
- App issues: https://github.com/The-OpenROAD-Project/OpenROAD/issues
- Flow issues: https://github.com/The-OpenROAD-Project/OpenROAD-flow-scripts/issues
- Discussions: the same GitHub org's Discussions tabs
- Email: openroad@ucsd.edu

---

## PART 4 — How ABC and OpenROAD Connect

They're two stages of one pipeline. The handoff is a **gate netlist**.

```
┌─────────────┐   Verilog   ┌──────────────────────────┐  gate      ┌──────────────────────────┐  GDSII
│   You / RTL │ ──────────► │  Yosys + ABC (LOGIC)     │ ─netlist─► │  OpenROAD (PHYSICAL)     │ ──────► fab
└─────────────┘             │  • strash → resyn2       │            │  • floorplan → place     │
                            │  • map to cells/LUTs     │            │  • CTS → route → signoff │
                            │  • cec (prove equal)     │            │  • STA (prove timing)    │
                            └──────────────────────────┘            └──────────────────────────┘
      "make the logic correct & small"                       "make the physical chip real & fast"
```

- **ABC** answers *"what gates?"* — it doesn't know coordinates.
- **OpenROAD** answers *"where and wired how?"* — it doesn't rethink your logic.
- Both are **command shells** that **read → transform → write**, and both keep
  score with metrics (ABC: `and`/`lev`; OpenROAD: Power/Performance/Area).

Because Yosys calls ABC internally, learning ABC directly improves your ability
to tune the whole flow.

---

## PART 5 — Cheat Sheets (keep these open)

### ABC command cheat sheet
| Command | Alias | Job |
|---------|-------|-----|
| `read file` | `r` | Load a design |
| `strash` | `st` | Convert to clean 2-input AIG |
| `balance` | `b` | Reduce depth / share logic |
| `rewrite` | `rw` | Replace small cuts with better subgraphs |
| `refactor` | `rf` | Collapse & re-factor a cone |
| `resub` | `rs` | Rebuild node from nearby nodes |
| `resyn2` | — | The workhorse optimize recipe (`b;rw;rf;...`) |
| `if -K 6` | — | Map to 6-input FPGA LUTs |
| `map` | — | Map to standard cells |
| `cec a b` | — | Prove two circuits equal |
| `fraig` | — | Merge functionally-equal nodes |
| `print_stats` | `ps` | Show `and` (area) / `lev` (depth) |
| `&get` / `&put` | — | Bridge classic ↔ GIA |
| `alias` | — | List all recipes/aliases live |
| `help rewrite` | — | Built-in help for any command |

### OpenROAD stage cheat sheet
| Order | Stage | Remember it as |
|-------|-------|----------------|
| 1 | Floorplan (+PDN) | "Draw the empty chip + power" |
| 2 | Placement | "Put gates somewhere legal" |
| 3 | CTS | "Balance the clock" |
| 4 | Routing | "Draw the wires" |
| 5 | Finishing | "Metal fill + cleanup" |
| 6 | Signoff | "Prove timing/power (STA + RC)" |

### The vocabulary you must not confuse
| Term | Means |
|------|-------|
| **RTL** | Verilog describing *behavior* (before any gates) |
| **Netlist** | A list of gates + how they connect (no positions yet) |
| **AIG** | And-Inverter Graph — logic as only 2-input ANDs + inversions |
| **LUT** | Lookup table — the programmable gate inside an FPGA |
| **Standard cell** | A pre-designed real gate (AND, FF, etc.) from a library |
| **Macro** | A big pre-made block (e.g. a memory) placed as one unit |
| **PPA** | Power, Performance, Area — the quality scorecard |
| **STA** | Static Timing Analysis — checks the chip meets its speed |
| **GDSII** | The final geometry file sent to the factory |
| **PDN** | Power Distribution Network — the on-chip power grid |
| **CTS** | Clock Tree Synthesis — balancing clock arrival times |

---

## PART 6 — Your fast track (if you only have limited time)

- **15 minutes:** read PART 1, PART 4, and the two cheat sheets in PART 5.
- **1 hour:** add PART 2 (ABC) and PART 3 (OpenROAD) in full.
- **Half a day:** do `abc_docs/07_HANDS_ON.md` — build ABC and run real sessions;
  then try the OpenROAD **Flow (ORFS)** on a sample design.
- **Deep dive (weeks):** follow `abc_docs/08_READING_PLAN.md` day-by-day, and the
  optional ML research pack in `ml_for_eda_research/abc_deep_dive/`.

### Sources this guide condenses
- Local ABC learning pack: `abc_docs/00_ONE_PAGE_OVERVIEW.md` … `08_READING_PLAN.md`
- `abc_documentation.txt` (index) + official ABC: https://people.eecs.berkeley.edu/~alanmi/abc/
- OpenROAD docs: https://theopenroadproject.org/welcome-to-openroads-documentation/
