"""Smoke tests for timing GNN (CPU, tiny graphs)."""

from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))


def test_forward():
    import torch
    from data.synthetic import make_synthetic_graph
    from models.timing_gnn import TimingGNN, TimingGNNConfig, analytic_fallback_slack

    g = make_synthetic_graph(n_nodes=32, seed=1)
    model = TimingGNN(TimingGNNConfig())
    out = model(g["x"], g["edge_index"], g["edge_attr"], g["endpoint_mask"])
    assert out["net_delay"].shape[0] == g["edge_index"].shape[1]
    assert out["slack"].shape[0] == g["x"].shape[0]
    fb = analytic_fallback_slack(g["x"])
    assert fb.shape[0] == g["x"].shape[0]
    loss = torch.nn.functional.mse_loss(out["net_delay"], g["net_delay"])
    loss.backward()
    print("PASS test_forward", float(loss.detach()))


def test_openroad_stub():
    from openroad_api.extract import extract_timing_graph

    eg = extract_timing_graph(None)
    assert eg.n_nodes == 0
    print("PASS test_openroad_stub", eg.note)


if __name__ == "__main__":
    test_forward()
    test_openroad_stub()
    print("ALL PASS")
