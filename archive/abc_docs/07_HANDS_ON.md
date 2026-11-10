# 07 — Hands-On Tutorial

Paths assume: `hardware_eda/abc`

---

## 1. Build

### Linux / WSL2 (recommended)

```bash
sudo apt install build-essential libreadline-dev
cd abc
make -j$(nproc) abc
# optional:
make libabc.a
make ABC_USE_PIC=1 libabc.so
```

If readline/pthreads fail:

```bash
make ABC_USE_NO_READLINE=1 ABC_USE_NO_PTHREADS=1 -j$(nproc)
```

### Windows

Official CI uses MSVC (`abcspace` / vcxproj). For learning + ML tooling, **WSL2
is far less painful**. See `abc/README.md` and `.github/workflows/build-windows.yml`.

---

## 2. Session A — classic `resyn2`

```bash
./abc
```

```
abc 01> read i10.aig
abc 02> ps
abc 03> strash
abc 04> ps
abc 05> resyn2
abc 06> ps
abc 07> if -K 6
abc 08> ps
abc 09> write_blif out_classic.blif
abc 10> quit
```

**What to notice:** `and` and `lev` after `resyn2`; LUT stats after `if`.

Batch form:

```bash
./abc -c "read i10.aig; strash; resyn2; if -K 6; print_stats"
```

---

## 3. Session B — GIA / ABC9

```
abc 01> read i10.aig
abc 02> &get
abc 03> &ps
abc 04> &syn2
abc 05> &ps
abc 06> &if -K 6
abc 07> &ps
abc 08> &put
abc 09> write_blif out_gia.blif
```

Compare runtime and quality vs Session A on larger AIGs later.

---

## 4. Session C — prove optimization safe

```bash
./abc -c "read i10.aig; strash; write_aiger a.aig; resyn2; write_aiger b.aig; cec a.aig b.aig"
```

---

## 5. Session D — explore aliases

```
abc 01> source abc.rc
abc 02> alias
abc 03> help rewrite
abc 04> help &syn2
```

Expand `resyn2` mentally into `b; rw; rf; ...` and run each step with `ps` between
them to see which step buys the most.

---

## 6. Session E — diminishing returns

```bash
./abc -c "read i10.aig; strash; ps; resyn2; ps; resyn2; ps; resyn2; ps"
```

Often the first `resyn2` helps most; later ones plateau — intuition behind
adaptive/ML recipes.

---

## 7. Benchmarks to grab next

| Suite | Why |
|-------|-----|
| EPFL combinational | modern, popular in papers |
| ISCAS’85 / ’89 | classic small nets |
| MCNC | older but still used |

Formats: prefer `.aig` or `.blif` for ABC.

---

## 8. Embedding ABC (preview)

See `src/demo.c`:

1. `make libabc.a`
2. Link a small C/C++ program calling ABC APIs
3. Or use Python bindings / ctypes against `libabc.so` (research setups)

APIs overview: `src/base/main/abcapis.h`

---

## Next

[08_READING_PLAN.md](08_READING_PLAN.md) — day-by-day source reading without drowning.
