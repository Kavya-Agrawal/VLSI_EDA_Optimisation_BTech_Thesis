# 04 — Command System (how ABC actually runs)

ABC’s UI is a **REPL**. Understanding dispatch unlocks the whole codebase.

---

## 1. Ways to run commands

### Interactive

```bash
./abc
abc 01> read i10.aig
abc 02> strash; resyn2; ps
```

### Batch (`-c`)

```bash
./abc -c "read i10.aig; strash; resyn2; print_stats"
```

### Script file

```bash
./abc -f myscript.scr
# or inside ABC:  source myscript.scr
```

At startup ABC sources `abc.rc` (aliases + default flags).

---

## 2. Dispatch pipeline

```
user string:  "b; rw; rf"
        │
        ▼
Cmd_CommandExecute()          src/base/cmd/
        │
        ├─ split on ';'
        ├─ expand aliases (tAliases)     e.g. rw → rewrite
        │                                 resyn2 → b; rw; rf; ...
        └─ lookup tCommands[name]
                │
                ▼
        Abc_CommandRewrite(pAbc, argc, argv)   src/base/abci/abc.c
                │
                ▼
        Abc_NtkRewrite(...)                    src/base/abci/abcRewrite.c
                │
                ▼
        Rwr_NodeRewrite(...)                   src/opt/rwr/rwrEva.c
```

**Pattern for every feature:**

```
CLI wrapper (abc.c)  →  driver (abci/abcXxx.c)  →  engine (opt|map|proof|gia)
```

---

## 3. How to find any command’s code (the 60-second method)

1. Decide the **real** command name (`alias` to expand if needed).
2. Grep in `src/base/abci/abc.c`:
   - `Cmd_CommandAdd( ..., "rewrite", ...)`
3. Jump to the handler `Abc_CommandRewrite`.
4. Follow the call into `abcRewrite.c` / `opt/...`.

For `&` commands, same idea — names start with `&` and usually call into `src/aig/gia/`.

---

## 4. Aliases vs real engines

**File:** `abc.rc`

| You type | Expands to | Engine world |
|----------|------------|--------------|
| `r` | `read` | IO |
| `st` | `strash` | classic AIG |
| `b` | `balance` | classic |
| `rw` | `rewrite` | `opt/rwr` |
| `rwz` | `rewrite -z` | accept zero-gain |
| `rf` | `refactor` | classic |
| `rs` | `resub` | classic |
| `ps` | `print_stats` | print |
| `resyn2` | `b; rw; rf; b; rw; rwz; b; rfz; rwz; b` | recipe |
| `&syn2` | (real command) | GIA script |

**Important:** `resyn2` is **not** one C algorithm. It is a **fixed sequence** of greedy passes. That is why recipe-level RL papers exist.

`&syn2` is different: implemented as GIA-native flow in `giaScript.c`, not as the classic alias string.

---

## 5. Classic ↔ GIA bridge commands

| Command | Effect |
|---------|--------|
| `&get` | copy/convert current classic network → `pGia` |
| `&put` | convert `pGia` → classic `pNtkCur` |
| `&ps` | print GIA stats |
| `&st` / other `&…` | operate only on GIA |

If a classic command “does nothing,” check you are not sitting only in GIA space (or vice versa).

---

## 6. Useful meta-commands

| Command | Use |
|---------|-----|
| `help` / `help rewrite` | built-in help text |
| `alias` | list aliases |
| `history` | previous commands |
| `undo` | restore backup network (if enabled) |
| `source file` | run a script |
| `time` | timing info |
| `print_stats` (`ps`) | nodes / levels / IO |

---

## 7. Adding your own command (mental sketch)

When you later extend ABC (or for ML hooks):

1. Write `int Abc_CommandMyThing(Abc_Frame_t*, int, char**)`
2. Register with `Cmd_CommandAdd` in the package init
3. Or drop sources under `src/ext*` — Makefile auto-picks those up

Embedding without the REPL: `Abc_Start()` / `Abc_Stop()` + APIs in `abcapis.h`
(see `src/demo.c`).

---

## Trace exercise (do this once)

1. Run: `./abc -c "read i10.aig; strash; rewrite; ps"`
2. Grep `"rewrite"` in `src/base/abci/abc.c`
3. Open `Abc_CommandRewrite` → `Abc_NtkRewrite` → `Rwr_NodeRewrite`
4. Note the cut size / gain check — that is the heart of the pass

---

## Next

[05_OPTIMIZATION_PASSES.md](05_OPTIMIZATION_PASSES.md) — what balance / rewrite / refactor / resub do.
