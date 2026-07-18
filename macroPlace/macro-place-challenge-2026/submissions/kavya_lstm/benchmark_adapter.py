"""Convert macro_place.Benchmark tensors to MaskPlace-style graph inputs."""

from __future__ import annotations

from typing import Dict, List, Set, Tuple

import torch

from macro_place.benchmark import Benchmark


def build_hard_macro_graph(
    benchmark: Benchmark, device: torch.device
) -> Tuple[torch.Tensor, torch.Tensor, List[str]]:
    """
    Build (features, adjacency, node_names) for hard macros only.

    Feature dim matches PointerOrderingModel (area, degree, w, h).
    """
    n_hard = benchmark.num_hard_macros
    names = benchmark.macro_names[:n_hard]
    sizes = benchmark.macro_sizes[:n_hard]

    node_to_nets: Dict[int, Set[int]] = {i: set() for i in range(n_hard)}
    for net_id, nodes in enumerate(benchmark.net_nodes):
        for node_idx in nodes.tolist():
            idx = int(node_idx)
            if idx < n_hard:
                node_to_nets[idx].add(net_id)

    node_info: Dict[str, Dict[str, float]] = {}
    for i, name in enumerate(names):
        w = float(sizes[i, 0].item())
        h = float(sizes[i, 1].item())
        node_info[name] = {"x": w, "y": h}

    node_to_net_dict: Dict[str, Set[int]] = {
        names[i]: node_to_nets[i] for i in range(n_hard)
    }

    from maskplace.graph_utils import build_graph

    return build_graph(node_info, node_to_net_dict, device)


def extract_hard_macro_edges(benchmark: Benchmark) -> Tuple[torch.Tensor, torch.Tensor]:
    """Undirected edges between hard macros with uniform weights."""
    n_hard = benchmark.num_hard_macros
    edge_weights: Dict[Tuple[int, int], float] = {}

    for nodes in benchmark.net_nodes:
        hard = sorted({int(n) for n in nodes.tolist() if int(n) < n_hard})
        if len(hard) < 2:
            continue
        w = 1.0 / (len(hard) - 1)
        for i in range(len(hard)):
            for j in range(i + 1, len(hard)):
                pair = (hard[i], hard[j])
                edge_weights[pair] = edge_weights.get(pair, 0.0) + w

    if not edge_weights:
        empty = torch.zeros(0, 2, dtype=torch.long)
        return empty, torch.zeros(0)

    edges = torch.tensor(list(edge_weights.keys()), dtype=torch.long)
    weights = torch.tensor([edge_weights[e] for e in edge_weights], dtype=torch.float32)
    return edges, weights


def degree_heuristic_order(benchmark: Benchmark) -> List[int]:
    """Fallback ordering: decreasing connectivity, then area."""
    n_hard = benchmark.num_hard_macros
    degree = [0] * n_hard
    for nodes in benchmark.net_nodes:
        hard = [int(n) for n in nodes.tolist() if int(n) < n_hard]
        for i in hard:
            degree[i] += 1
    areas = (benchmark.macro_sizes[:n_hard, 0] * benchmark.macro_sizes[:n_hard, 1]).tolist()
    return sorted(range(n_hard), key=lambda i: (-degree[i], -areas[i]))
