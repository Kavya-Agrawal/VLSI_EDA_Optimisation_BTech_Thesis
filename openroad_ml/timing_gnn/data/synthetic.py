"""Synthetic circuit graphs for smoke training (no CircuitOps required)."""

from __future__ import annotations

import torch


def make_synthetic_graph(
    n_nodes: int = 64,
    n_edges: int | None = None,
    node_dim: int = 16,
    edge_dim: int = 8,
    seed: int = 0,
) -> dict[str, torch.Tensor]:
    g = torch.Generator().manual_seed(seed)
    if n_edges is None:
        n_edges = n_nodes * 3
    x = torch.rand(n_nodes, node_dim, generator=g)
    # Prefer forward edges for a DAG-ish timing graph
    src = torch.randint(0, max(1, n_nodes - 1), (n_edges,), generator=g)
    dst = src + torch.randint(1, max(2, n_nodes // 4), (n_edges,), generator=g)
    dst = dst.clamp(max=n_nodes - 1)
    edge_index = torch.stack([src, dst], dim=0)
    edge_attr = torch.rand(n_edges, edge_dim, generator=g)
    # Toy labels: delay ~ edge length proxy + fanout
    net_delay = edge_attr[:, 0] + 0.1 * x[src, 0]
    # Endpoints = sinks with low out-degree proxy
    endpoint_mask = torch.zeros(n_nodes)
    endpoint_mask[-max(1, n_nodes // 8) :] = 1.0
    slack = 1.0 - (x[:, 0] + x[:, 1]) * endpoint_mask
    return {
        "x": x,
        "edge_index": edge_index,
        "edge_attr": edge_attr,
        "net_delay": net_delay,
        "slack": slack,
        "endpoint_mask": endpoint_mask,
    }


class SyntheticTimingDataset(torch.utils.data.Dataset):
    def __init__(self, n_graphs: int = 32, **kwargs):
        self.graphs = [make_synthetic_graph(seed=i, **kwargs) for i in range(n_graphs)]

    def __len__(self) -> int:
        return len(self.graphs)

    def __getitem__(self, idx: int) -> dict[str, torch.Tensor]:
        return self.graphs[idx]
