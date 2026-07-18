"""Placement logic: ordering, wirelength-aware placement, SA refinement."""

from __future__ import annotations

import math
import random
from pathlib import Path
from typing import List, Optional, Tuple

import numpy as np
import torch

from macro_place.benchmark import Benchmark

from benchmark_adapter import (
    build_hard_macro_graph,
    degree_heuristic_order,
    extract_hard_macro_edges,
)
from legalize import legalize_hard_macros


def _wirelength_cost(
    pos: np.ndarray, edges: np.ndarray, edge_weights: np.ndarray
) -> float:
    if len(edges) == 0:
        return 0.0
    dx = np.abs(pos[edges[:, 0], 0] - pos[edges[:, 1], 0])
    dy = np.abs(pos[edges[:, 0], 1] - pos[edges[:, 1], 1])
    return float((edge_weights * (dx + dy)).sum())


def _build_neighbors(n: int, edges: np.ndarray) -> List[List[int]]:
    neighbors: List[List[int]] = [[] for _ in range(n)]
    for i, j in edges:
        neighbors[i].append(j)
        neighbors[j].append(i)
    return neighbors


def place_in_order(
    initial_pos: np.ndarray,
    order: List[int],
    movable: np.ndarray,
    sizes: np.ndarray,
    neighbors: List[List[int]],
    canvas_w: float,
    canvas_h: float,
) -> np.ndarray:
    """Sequential placement: each macro moves toward placed neighbors."""
    n = len(order)
    half_w = sizes[:, 0] / 2.0
    half_h = sizes[:, 1] / 2.0
    pos = initial_pos.copy()
    placed: set = set()

    for idx in order:
        if not movable[idx]:
            placed.add(idx)
            continue

        nbrs = [j for j in neighbors[idx] if j in placed]
        if nbrs:
            cx = float(np.mean([pos[j, 0] for j in nbrs]))
            cy = float(np.mean([pos[j, 1] for j in nbrs]))
        else:
            cx, cy = float(pos[idx, 0]), float(pos[idx, 1])

        pos[idx, 0] = np.clip(cx, half_w[idx], canvas_w - half_w[idx])
        pos[idx, 1] = np.clip(cy, half_h[idx], canvas_h - half_h[idx])
        placed.add(idx)

    return pos


def sa_refine(
    pos: np.ndarray,
    edges: np.ndarray,
    edge_weights: np.ndarray,
    movable: np.ndarray,
    sizes: np.ndarray,
    canvas_w: float,
    canvas_h: float,
    iters: int,
    seed: int,
) -> np.ndarray:
    """Light simulated annealing on hard macros with overlap rejection."""
    if len(edges) == 0 or not movable.any():
        return pos

    random.seed(seed)
    np.random.seed(seed)

    n = pos.shape[0]
    half_w = sizes[:, 0] / 2.0
    half_h = sizes[:, 1] / 2.0
    sep_x = (sizes[:, 0:1] + sizes[:, 0:1].T) / 2.0
    sep_y = (sizes[:, 1:2] + sizes[:, 1:2].T) / 2.0
    movable_idx = np.where(movable)[0]
    neighbors = _build_neighbors(n, edges)

    def wl_cost() -> float:
        return _wirelength_cost(pos, edges, edge_weights)

    def has_overlap(idx: int) -> bool:
        gap = 0.05
        dx = np.abs(pos[idx, 0] - pos[:, 0])
        dy = np.abs(pos[idx, 1] - pos[:, 1])
        overlaps = (dx < sep_x[idx] + gap) & (dy < sep_y[idx] + gap)
        overlaps[idx] = False
        return bool(overlaps.any())

    current = wl_cost()
    best_pos = pos.copy()
    best_cost = current

    t_start = max(canvas_w, canvas_h) * 0.12
    t_end = max(canvas_w, canvas_h) * 0.001

    for step in range(iters):
        frac = step / max(iters, 1)
        t = t_start * (t_end / t_start) ** frac
        i = int(np.random.choice(movable_idx))
        old_x, old_y = pos[i, 0], pos[i, 1]
        shift = t * (0.3 + 0.7 * (1.0 - frac))
        pos[i, 0] = np.clip(pos[i, 0] + np.random.normal(0, shift), half_w[i], canvas_w - half_w[i])
        pos[i, 1] = np.clip(pos[i, 1] + np.random.normal(0, shift), half_h[i], canvas_h - half_h[i])

        if has_overlap(i):
            pos[i, 0], pos[i, 1] = old_x, old_y
            continue

        new_cost = wl_cost()
        delta = new_cost - current
        if delta < 0 or random.random() < math.exp(-delta / max(t, 1e-10)):
            current = new_cost
            if current < best_cost:
                best_cost = current
                best_pos = pos.copy()
        else:
            pos[i, 0], pos[i, 1] = old_x, old_y

    return best_pos


def lstm_order_indices(
    benchmark: Benchmark,
    model: torch.nn.Module,
    device: torch.device,
    seed: int,
) -> List[int]:
    """Greedy decode from LSTM pointer model (deterministic given seed)."""
    torch.manual_seed(seed)
    x, adj, node_names = build_hard_macro_graph(benchmark, device)
    x = x.to(device)
    adj = adj.to(device)

    with torch.no_grad():
        embeddings = model.encoder(x, adj)

    n = embeddings.shape[0]
    decoder = model.decoder
    mask = torch.zeros(n, device=device)
    selected: List[int] = []
    h = torch.zeros(1, embeddings.shape[1], device=device)
    c = torch.zeros(1, embeddings.shape[1], device=device)
    inp = embeddings.mean(dim=0, keepdim=True)

    for _ in range(n):
        h, c = decoder.lstm(inp, (h, c))
        query = decoder.W_q(h)
        keys = decoder.W_k(embeddings)
        scores = decoder.v(torch.tanh(query + keys)).squeeze(-1)
        masked_scores = scores + mask
        idx = int(torch.argmax(masked_scores).item())
        selected.append(idx)
        mask[idx] = -1e9
        inp = embeddings[idx].unsqueeze(0)

    return selected


def load_ordering_model(weights_dir: Path, device: torch.device) -> Optional[torch.nn.Module]:
    """Load PointerOrderingModel if checkpoint exists."""
    candidates = [
        weights_dir / "ordering_lstm.pth",
        weights_dir / "model_best.pth",
        weights_dir / "model_best_adaptec4.pth",
    ]
    ckpt_path = next((p for p in candidates if p.is_file()), None)
    if ckpt_path is None:
        return None

    from maskplace.pointer_model import PointerOrderingModel

    model = PointerOrderingModel().to(device)
    state = torch.load(ckpt_path, map_location=device, weights_only=False)
    if isinstance(state, dict) and "state_dict" in state:
        state = state["state_dict"]
    model.load_state_dict(state)
    model.eval()
    return model


def place_hard_macros(
    benchmark: Benchmark,
    weights_dir: Path,
    seed: int = 42,
    order_samples: int = 5,
    sa_iters: int = 2500,
) -> torch.Tensor:
    """
    Full pipeline for hard macros; soft macros stay at initial positions.
    """
    n_hard = benchmark.num_hard_macros
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

    placement = benchmark.macro_positions.clone()
    sizes = benchmark.macro_sizes[:n_hard].numpy().astype(np.float64)
    movable = (
        benchmark.get_movable_mask()[:n_hard] & benchmark.get_hard_macro_mask()[:n_hard]
    ).numpy()

    edges_t, weights_t = extract_hard_macro_edges(benchmark)
    edges = edges_t.numpy() if len(edges_t) else np.zeros((0, 2), dtype=np.int64)
    weights = weights_t.numpy() if len(weights_t) else np.zeros(0, dtype=np.float64)
    neighbors = _build_neighbors(n_hard, edges)

    cw = float(benchmark.canvas_width)
    ch = float(benchmark.canvas_height)

    model = load_ordering_model(weights_dir, device)
    orders: List[List[int]] = []

    if model is not None:
        for s in range(order_samples):
            orders.append(lstm_order_indices(benchmark, model, device, seed + s))
    orders.append(degree_heuristic_order(benchmark))

    best_pos = placement[:n_hard].numpy().astype(np.float64)
    best_wl = float("inf")

    initial = placement[:n_hard].numpy().astype(np.float64)
    for order in orders:
        pos = place_in_order(initial, order, movable, sizes, neighbors, cw, ch)
        pos = legalize_hard_macros(pos, movable, sizes, cw, ch)
        wl = _wirelength_cost(pos, edges, weights)
        if wl < best_wl:
            best_wl = wl
            best_pos = pos.copy()

    iters = min(sa_iters, max(800, n_hard * 8))
    best_pos = sa_refine(
        best_pos, edges, weights, movable, sizes, cw, ch, iters, seed
    )
    best_pos = legalize_hard_macros(best_pos, movable, sizes, cw, ch)

    placement[:n_hard] = torch.tensor(best_pos, dtype=placement.dtype)
    fixed = benchmark.macro_fixed
    placement[fixed] = benchmark.macro_positions[fixed]
    return placement
