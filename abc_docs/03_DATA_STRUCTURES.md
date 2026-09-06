# 03 — Core Data Structures (need-to-know)

If you understand these three objects, ABC stops looking like a random pile of `.c` files:

1. `Abc_Frame_t` — the process / REPL state  
2. `Abc_Ntk_t` / `Abc_Obj_t` — classic network  
3. `Gia_Man_t` / `Gia_Obj_t` — modern AIG  

---

## 1. The frame — `Abc_Frame_t`

**File:** `src/base/main/mainInt.h`

Singleton accessed via `Abc_FrameGetGlobalFrame()`.

Important fields:

| Field | Meaning |
|-------|---------|
| `tCommands` | hash: command name → C function |
| `tAliases` | hash: `rw` → `rewrite`, `resyn2` → script |
| `pNtkCur` | current classic network |
| `pGia` | current GIA network |
| `pLibLut`, `pLibScl`, `pLibGen`, … | loaded libraries |
| `vStore` | networks stored for `choice` / fraig_store |
| `pCex` | counterexample from failed verification |

Every command handler looks like:

```c
int Abc_CommandSomething( Abc_Frame_t * pAbc, int argc, char ** argv );
```

It reads `pAbc->pNtkCur` or `pAbc->pGia`, mutates/replaces it, returns status.

---

## 2. Classic network — `Abc_Ntk_t` / `Abc_Obj_t`

**File:** `src/base/abc/abc.h`

### Network types (simplified)

| Type | Meaning |
|------|---------|
| NETLIST | gates + nets (after some reads) |
| LOGIC | nodes with SOP / functions |
| **STRASH** | AIG of 2-AND + complemented edges — what optimizers want |

`strash` gets you to STRASH.

### Objects

`Abc_Obj_t` = PI, PO, latch, or AND/node.

- Fanins / fanouts are **integer IDs** into `pNtk->vObjs` (via vector APIs).
- Iterate with macros like `Abc_NtkForEachNode`, `Abc_ObjForEachFanin`.

### Complemented edges (critical concept)

Inversion is **not** usually a separate NOT node. It is a flag on the edge.

Two encodings you will see:

1. Bits on the object: `fCompl0`, `fCompl1`
2. **Pointer tagging:** LSB of an `Abc_Obj_t*` means complemented  
   - `Abc_ObjNot(p)` XORs the pointer with `1`  
   - `Abc_ObjRegular(p)` clears that bit  

Once this clicks, AIG code becomes readable.

### Structural hashing

**File:** `src/base/abc/abcAig.c`

`Abc_AigAnd(a, b)`:

1. Canonicalize order / polarity of fanins  
2. Look up `(fanin0, fanin1, compl bits)` in a hash table  
3. Reuse existing node if found; otherwise create  

This is why rewriting can **share** logic and report node savings.

---

## 3. GIA — `Gia_Man_t` / `Gia_Obj_t`

**File:** `src/aig/gia/gia.h`

Designed for **scalability** (cache-friendly, tiny nodes).

### One node (~16 bytes)

```c
struct Gia_Obj_t_ {
    unsigned iDiff0 : 29;   // fanin0 index = thisIndex - iDiff0
    unsigned fCompl0: 1;
    ...
    unsigned iDiff1 : 29;   // fanin1 as relative offset
    unsigned fCompl1: 1;
    ...
    unsigned Value;         // scratch / hash link / copy map
};
```

All nodes live in **one dense array** `pGia->pObjs[]`.

### Literals

APIs use **literals**, not raw node IDs:

```
lit = 2 * var + complement
```

Helpers: `Abc_Var2Lit`, `Abc_Lit2Var`, `Abc_LitIsCompl`, …

Creating ANDs: `Gia_ManHashAnd(p, lit0, lit1)` → returns literal of result.

### What GIA does *not* always store

Fanout lists are often **optional / computed on demand**. Many passes use:
- levels (`vLevels`)
- reference counts (`vRefs`)
- the `Value` scratch field

---

## 4. Classic vs GIA (side by side)

| | Classic `Abc_Ntk_t` | GIA `Gia_Man_t` |
|--|--------------------|-----------------|
| Node size | larger object structs | tiny bitfields |
| Fanins | ID vectors | relative offsets |
| Commands | `rw`, `resyn2`, `if` | `&b`, `&syn2`, `&if` |
| Held in frame | `pNtkCur` | `pGia` |
| Bridge | `&get` / `&put` | |

**Practical advice:** learn classic first (matches `abc.rc` scripts), then GIA
(matches industrial-scale `&` flows).

---

## 5. Utility types you will see constantly

**Package:** `src/misc/vec/`

| Type | Holds |
|------|-------|
| `Vec_Int_t` | dynamic array of `int` |
| `Vec_Ptr_t` | dynamic array of pointers |
| `Vec_Wec_t` | vector-of-vectors |
| `Vec_Str_t` | bytes / strings |

Macros (learn these):

```c
Vec_IntForEachEntry( v, entry, i ) { ... }
Vec_IntPush( v, x );
Vec_IntSize( v );
```

Hash tables: `src/misc/st/` (`st__table` used for commands/aliases).

---

## 6. Where temporary per-node data lives

Algorithms rarely allocate a parallel array for everything. Common patterns:

| World | Scratch field | Typical use |
|-------|---------------|-------------|
| GIA | `pObj->Value` | copy map, hash next, trav id payload |
| Classic | `pObj->pCopy`, marks, `Value`-like fields | duplication / mapping |

When confused about dataflow, search the pass for writes to `Value` / `pCopy`.

---

## Mini exercise

Open these three headers and skim only the struct definitions (ignore functions):

1. `src/base/main/mainInt.h` → `Abc_Frame_t_`
2. `src/base/abc/abc.h` → `Abc_Ntk_t_`, `Abc_Obj_t_`
3. `src/aig/gia/gia.h` → `Gia_Obj_t_`, `Gia_Man_t_`

You now have the vocabulary for the rest of ABC.

---

## Next

[04_COMMAND_SYSTEM.md](04_COMMAND_SYSTEM.md) — how typing `rw` becomes a C call.
