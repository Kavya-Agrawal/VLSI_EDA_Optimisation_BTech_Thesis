# 04 — ML Integration Guide: wiring a model into ABC

> From "I have ABC and PyTorch" to "a learned policy is making decisions inside a
> synthesis pass." Four integration levels, ordered by increasing coupling.
> Recommended platform: **WSL2/Linux** (all commands below assume it).

---

## Level 0 — Subprocess loop (prototype in an afternoon)

What DRiLLS does. No C code at all.

```python
import subprocess, re

def run_abc(script: str) -> dict:
    out = subprocess.run(["./abc", "-c", script], capture_output=True, text=True).stdout
    m = re.search(r"and\s*=\s*(\d+).*?lev\s*=\s*(\d+)", out, re.S)
    return {"nodes": int(m.group(1)), "levels": int(m.group(2))}

state = run_abc("read i10.aig; strash; print_stats")
after = run_abc("read i10.aig; strash; rewrite; print_stats")
print("gain:", state["nodes"] - after["nodes"])
```

Good for: recipe-level RL, data collection. 
Bad for: anything per-node (process startup + file I/O dominates), which is
exactly why the novel directions in doc 03 need Levels 1–3.

---

## Level 1 — Persistent ABC session via `libabc` (the workhorse)

Build the shared library and drive ABC in-process from Python. One process, one
loaded network, thousands of commands per second.

```bash
cd abc && make ABC_USE_PIC=1 -j$(nproc) libabc.so
```

### Option A: ctypes (zero build tooling)

```python
import ctypes
abc = ctypes.CDLL("./libabc.so")
abc.Abc_Start()
frame = abc.Abc_FrameGetGlobalFrame()
def cmd(s: str) -> int:
    return abc.Cmd_CommandExecute(frame, s.encode())
cmd("read i10.aig; strash")
cmd("rewrite")           # state persists between calls!
cmd("print_stats")
abc.Abc_Stop()
```

### Option B: pybind11 (the `abc_py` pattern — typed access to internals)

```cpp
// binding.cpp  — compile against libabc.a, include ABC headers
#include <pybind11/pybind11.h>
#include "base/main/main.h"
#include "base/main/mainInt.h"
#include "aig/gia/gia.h"

namespace py = pybind11;

struct AbcSession {
    Abc_Frame_t* f;
    AbcSession()  { Abc_Start(); f = Abc_FrameGetGlobalFrame(); }
    ~AbcSession() { Abc_Stop(); }
    int  cmd(const std::string& s) { return Cmd_CommandExecute(f, s.c_str()); }
    py::dict gia_stats() {
        Gia_Man_t* g = Abc_FrameReadGia(f);          // after "&get"
        py::dict d;
        d["ands"]   = Gia_ManAndNum(g);
        d["levels"] = Gia_ManLevelNum(g);
        d["pis"]    = Gia_ManPiNum(g);
        d["pos"]    = Gia_ManPoNum(g);
        return d;                                     // no text parsing!
    }
};

PYBIND11_MODULE(abcpy, m) {
    py::class_<AbcSession>(m, "AbcSession")
        .def(py::init<>())
        .def("cmd", &AbcSession::cmd)
        .def("gia_stats", &AbcSession::gia_stats);
}
```

```bash
c++ -O2 -shared -fPIC $(python3 -m pybind11 --includes) binding.cpp \
    -Iabc/src abc/libabc.a -o abcpy$(python3-config --extension-suffix) \
    -lpthread -ldl -lm
```

This is the right level for **recipe RL, feature extraction, and graph export**.

### Exporting the AIG as a graph (for GNNs)

Walk the GIA directly instead of writing files:

```cpp
py::tuple edges(AbcSession& s) {
    Gia_Man_t* g = Abc_FrameReadGia(s.f);
    std::vector<int> src, dst, compl_;
    Gia_Obj_t* pObj; int i;
    Gia_ManForEachAnd(g, pObj, i) {
        src.push_back(Gia_ObjFaninId0(pObj, i)); dst.push_back(i);
        compl_.push_back(Gia_ObjFaninC0(pObj));
        src.push_back(Gia_ObjFaninId1(pObj, i)); dst.push_back(i);
        compl_.push_back(Gia_ObjFaninC1(pObj));
    }
    return py::make_tuple(src, dst, compl_);   // → torch_geometric edge_index
}
```

---

## Level 2 — Custom ABC command (feature dumping & data generation)

Add your own command without touching the giant `abc.c`, using the extension
module mechanism (`src/ext*` dirs are auto-picked-up by the Makefile).

```
abc/src/ext_mlhooks/
├── module.make          # ONE line:  SRC += src/ext_mlhooks/mlHooks.c
└── mlHooks.c
```

```c
// mlHooks.c — registers "ml_features": dumps per-node features as CSV
#include "base/main/mainInt.h"
#include "base/cmd/cmd.h"
#include "base/abc/abc.h"

static int Ml_CommandFeatures(Abc_Frame_t* pAbc, int argc, char** argv)
{
    Abc_Ntk_t* pNtk = Abc_FrameReadNtk(pAbc);
    Abc_Obj_t* pObj; int i;
    if (!pNtk || !Abc_NtkIsStrash(pNtk)) {
        Abc_Print(-1, "ml_features: need a strashed network (run strash).\n");
        return 1;
    }
    printf("id,level,fanouts,fanin0,fanin1\n");
    Abc_NtkForEachNode(pNtk, pObj, i)
        printf("%d,%d,%d,%d,%d\n", Abc_ObjId(pObj), Abc_ObjLevel(pObj),
               Abc_ObjFanoutNum(pObj), Abc_ObjFaninId0(pObj), Abc_ObjFaninId1(pObj));
    return 0;
}

static void Ml_Init(Abc_Frame_t* pAbc)
{ Cmd_CommandAdd(pAbc, "ML", "ml_features", Ml_CommandFeatures, 0); }

static Abc_FrameInitializer_t s_Init = { Ml_Init, NULL, NULL, NULL };

// constructor runs before main() → registration is automatic
__attribute__((constructor)) static void Ml_Register(void)
{ Abc_FrameAddInitializer(&s_Init); }
```

Rebuild (`make -j abc`) → `abc -c "read x.aig; strash; ml_features"` streams a
dataset. Extend the same skeleton to log **decision-point features + outcomes**
(e.g., inside a copy of `Abc_NtkResubstitute`: dump divisor features + which
resub succeeded) — that's your supervised training data for project 2.1/2.2.

---

## Level 3 — Learned policy *inside* a pass (the research contribution)

Replace a heuristic decision with model inference in C. Two deployment patterns:

### Pattern A: ONNX Runtime C API (recommended)

Train in PyTorch → `torch.onnx.export` → load with onnxruntime's C API inside
ABC. Keep the model tiny (MLP/GBDT-distilled) so inference is ~µs.

```c
// sketch: score divisors inside Abc_ManResubEval (abcResub.c)
#include <onnxruntime_c_api.h>
static OrtSession* g_sess = NULL;      // load once in Ml_Init

float Ml_ScoreDivisor(float* feat, int n) {
    // build OrtValue over feat[n], run g_sess, return output[0]
}

// in the divisor loop, replace fixed 0→1→2→3 order with:
//   sort candidates by Ml_ScoreDivisor(features(div))
//   try in that order, keep the existing SAT/sim validation
```

Key engineering rules learned from SLAP/LEAP:
1. **Never remove the correctness check** — the model only re-orders/prunes
   *candidates*; equivalence is still verified by truth table/SAT. QoR can't
   become wrong, only better/worse.
2. **Batch inference** where possible (score all divisors of a window in one call).
3. **Always keep a `-ml off` flag** so you can A/B the learned vs stock heuristic
   in the same binary — this is your experiment table.

### Pattern B: filesystem/socket oracle (for prototyping only)

The pass writes features to a pipe, a Python server answers scores. 100–1000×
slower, but lets you iterate on the model without recompiling ABC. Use it to
validate the idea, then freeze to ONNX.

---

## The full research loop (putting it together)

```
                    ┌──────────────────────────────────────────┐
                    │ 1. INSTRUMENT (Level 2 command)           │
                    │    run stock pass, log features+outcomes  │
                    └───────────────┬──────────────────────────┘
                                    ▼
                    ┌──────────────────────────────────────────┐
                    │ 2. TRAIN offline (PyTorch / LightGBM)     │
                    │    predict: gain / success / best-choice  │
                    └───────────────┬──────────────────────────┘
                                    ▼
                    ┌──────────────────────────────────────────┐
                    │ 3. DEPLOY (Level 3, ONNX in the pass)     │
                    │    model re-ranks candidates; checks stay │
                    └───────────────┬──────────────────────────┘
                                    ▼
                    ┌──────────────────────────────────────────┐
                    │ 4. EVALUATE  (Level 1 harness)            │
                    │    EPFL/OpenABC-D: nodes, levels, runtime │
                    │    + downstream: if -K6 area/delay        │
                    │    vs stock ABC with -ml off              │
                    └──────────────────────────────────────────┘
```

Optional step 5 (upgrade to RL): once supervised re-ranking works, use the
Level 1 harness as a gym environment (state = graph features, action =
candidate choice, reward = verified gain) and fine-tune the policy with PPO —
directly reusing the actor-critic experience from your MaskPlace project.

---

## Practical gotchas

- **Windows:** native MSVC builds work (Win32 + pthreads-win32; see
  `.github/workflows/build-windows.yml`) but every ML tool in this stack assumes
  Linux — use WSL2 and keep everything (abc, Python, data) inside the WSL
  filesystem for speed.
- **Determinism:** ABC passes are deterministic given the same visit order; when
  you change candidate ordering, node IDs downstream shift. Compare *metrics*,
  not graphs.
- **`pObj->Value` / `pCopy` discipline:** passes stash temp data there; if your
  instrumentation also uses them you'll corrupt the pass. Use your own arrays
  keyed by `Abc_ObjId`.
- **Timing:** always report wall-clock of the *whole* command (`time ./abc -c ...`)
  — an ML model that improves QoR 1% but doubles runtime loses in synthesis.
- **Benchmark hygiene:** train/test split by *circuit family* (EPFL arithmetic vs
  random-control), never by random node split — leakage across a circuit is the
  classic ML-EDA reviewing complaint.
