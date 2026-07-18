"""SYNAPSE smoke tests.

Runs without a GPU. Parts needing torch/onnx self-skip if those aren't
installed, so this is safe on any machine:

    cd abc/src/ext_ml/python
    python -m tests.test_smoke

Checks:
  1. config dimensions are internally consistent and match ml_abc.h values.
  2. the GIA feature-dump parser round-trips a synthetic file.
  3. the decision-CSV parser reads rows.
  4. (if torch present) the model builds and does a forward pass.
  5. (if torch present) ONNX export produces a file with the C-expected I/O.
"""

from __future__ import annotations

import os
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

PASS, FAIL, SKIP = "PASS", "FAIL", "SKIP"
results = []


def check(name, fn):
    try:
        r = fn()
        results.append((r or PASS, name, ""))
    except _Skip as s:
        results.append((SKIP, name, str(s)))
    except Exception as e:  # noqa: BLE001
        results.append((FAIL, name, f"{type(e).__name__}: {e}"))


class _Skip(Exception):
    pass


# ---------------------------------------------------------------- tests ----
def t_config():
    import config as C
    assert C.NODE_FEAT_DIM == 16, C.NODE_FEAT_DIM
    assert C.DIV_FEAT_DIM == 12, C.DIV_FEAT_DIM
    assert C.EMB_DIM == 64
    assert len(C.NODE_FEATURE_NAMES) == C.NODE_FEAT_DIM
    cfg = C.SynapseConfig()
    assert cfg.rank_input_dim() == 2 * C.EMB_DIM + C.DIV_FEAT_DIM


def t_gia_parser():
    from data.dataset import load_gia_graph
    import config as C
    # synthetic dump: 3 AND nodes (ids 3,5,6), 2 edges among them
    lines = [f"NODES 3 {C.NODE_FEAT_DIM}"]
    for gid in (3, 5, 6):
        lines.append(str(gid) + " " + " ".join("0.5" for _ in range(C.NODE_FEAT_DIM)))
    lines += ["EDGES 2", "3 5 0", "3 6 1"]
    with tempfile.NamedTemporaryFile("w", suffix=".txt", delete=False) as fh:
        fh.write("\n".join(lines) + "\n")
        path = fh.name
    try:
        x, edge_index, edge_attr, id_map = load_gia_graph(path)
        # numpy path (no torch): x is ndarray [3,16]; edges tuple
        n_nodes = x.shape[0] if hasattr(x, "shape") else len(x)
        assert n_nodes == 3, n_nodes
        assert id_map == {3: 0, 5: 1, 6: 2}, id_map
    finally:
        os.remove(path)


def t_csv_parser():
    from data.dataset import DecisionCSV
    import config as C
    rows = ["# header", "1,1.0," + ",".join("0.1" for _ in range(C.DIV_FEAT_DIM)),
            "1,0.0," + ",".join("0.2" for _ in range(C.DIV_FEAT_DIM))]
    with tempfile.NamedTemporaryFile("w", suffix=".csv", delete=False) as fh:
        fh.write("\n".join(rows) + "\n")
        path = fh.name
    try:
        ds = DecisionCSV(path, task=1)
        assert len(ds) == 2, len(ds)
    finally:
        os.remove(path)


def t_model_forward():
    try:
        import torch  # noqa: F401
    except Exception:
        raise _Skip("torch not installed")
    import config as C
    from models.synapse import SynapseModel

    class Batch:
        pass

    cfg = C.SynapseConfig(encoder="aigconv", emb_dim=32, prop_steps=2)
    model = SynapseModel(cfg)
    import torch
    b = Batch()
    b.x = torch.zeros((5, C.NODE_FEAT_DIM))
    b.edge_index = torch.tensor([[0, 1, 2], [3, 4, 3]], dtype=torch.long)
    b.edge_attr = torch.zeros((3, 1))
    b.cand_pairs = None
    out = model(b)
    assert out["potential"].shape[0] == 5, out["potential"].shape


def t_onnx_export():
    try:
        import torch  # noqa: F401
        import onnx  # noqa: F401
    except Exception:
        raise _Skip("torch/onnx not installed")
    from export.to_onnx import build_export_wrapper
    import config as C
    import torch
    cfg = C.SynapseConfig()
    w = build_export_wrapper(cfg)
    nf = torch.zeros((1, C.NODE_FEAT_DIM))
    rf = torch.zeros((1, C.DIV_FEAT_DIM))
    with tempfile.NamedTemporaryFile(suffix=".onnx", delete=False) as fh:
        path = fh.name
    try:
        torch.onnx.export(w, (nf, rf), path,
                          input_names=["node_feat", "rank_feat"],
                          output_names=["potential", "window_payoff", "score"],
                          opset_version=17)
        import onnx
        m = onnx.load(path)
        names = {i.name for i in m.graph.input}
        assert {"node_feat", "rank_feat"} <= names, names
    finally:
        if os.path.exists(path):
            os.remove(path)


def main():
    for name, fn in [
        ("config dims", t_config),
        ("gia feature parser", t_gia_parser),
        ("decision csv parser", t_csv_parser),
        ("model forward (torch)", t_model_forward),
        ("onnx export (torch+onnx)", t_onnx_export),
    ]:
        check(name, fn)

    print("\nSYNAPSE smoke test results")
    print("-" * 48)
    ok = 0
    for status, name, msg in results:
        line = f"  {status:4}  {name}"
        if msg:
            line += f"   ({msg})"
        print(line)
        ok += status == PASS
    fails = sum(1 for s, _, _ in results if s == FAIL)
    print("-" * 48)
    print(f"  {ok} passed, {fails} failed, "
          f"{sum(1 for s, _, _ in results if s == SKIP)} skipped")
    sys.exit(1 if fails else 0)


if __name__ == "__main__":
    main()
