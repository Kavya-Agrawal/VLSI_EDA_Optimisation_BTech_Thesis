"""Hard-macro legalization (zero overlaps, canvas bounds)."""

from __future__ import annotations

import numpy as np


def legalize_hard_macros(
    pos: np.ndarray,
    movable: np.ndarray,
    sizes: np.ndarray,
    canvas_w: float,
    canvas_h: float,
    gap: float = 0.05,
) -> np.ndarray:
    """
    Resolve overlaps with minimum displacement from current positions.

    pos: [N, 2] center coordinates for hard macros only.
    """
    n = pos.shape[0]
    half_w = sizes[:, 0] / 2.0
    half_h = sizes[:, 1] / 2.0
    sep_x = (sizes[:, 0:1] + sizes[:, 0:1].T) / 2.0 + gap
    sep_y = (sizes[:, 1:2] + sizes[:, 1:2].T) / 2.0 + gap

    order = sorted(range(n), key=lambda i: -sizes[i, 0] * sizes[i, 1])
    placed = np.zeros(n, dtype=bool)
    legal = pos.copy().astype(np.float64)

    for idx in order:
        if not movable[idx]:
            placed[idx] = True
            continue

        if placed.any():
            dx = np.abs(legal[idx, 0] - legal[:, 0])
            dy = np.abs(legal[idx, 1] - legal[:, 1])
            conflict = (dx < sep_x[idx]) & (dy < sep_y[idx]) & placed
            conflict[idx] = False
            if not conflict.any():
                placed[idx] = True
                continue

        step = max(float(sizes[idx, 0]), float(sizes[idx, 1])) * 0.25
        best_p = legal[idx].copy()
        best_d = float("inf")

        for r in range(1, 150):
            found = False
            for dxm in range(-r, r + 1):
                for dym in range(-r, r + 1):
                    if abs(dxm) != r and abs(dym) != r:
                        continue
                    cx = np.clip(pos[idx, 0] + dxm * step, half_w[idx], canvas_w - half_w[idx])
                    cy = np.clip(pos[idx, 1] + dym * step, half_h[idx], canvas_h - half_h[idx])
                    if placed.any():
                        dx = np.abs(cx - legal[:, 0])
                        dy = np.abs(cy - legal[:, 1])
                        c = (dx < sep_x[idx]) & (dy < sep_y[idx]) & placed
                        c[idx] = False
                        if c.any():
                            continue
                    d = (cx - pos[idx, 0]) ** 2 + (cy - pos[idx, 1]) ** 2
                    if d < best_d:
                        best_d = d
                        best_p = np.array([cx, cy], dtype=np.float64)
                        found = True
            if found:
                break

        legal[idx] = best_p
        placed[idx] = True

    return legal.astype(np.float32)
