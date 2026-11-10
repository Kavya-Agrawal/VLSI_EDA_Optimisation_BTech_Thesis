"""Dump / inject congestion maps via OpenROAD (stubs)."""

from __future__ import annotations

from typing import Any


def try_import_openroad():
    try:
        import openroad  # type: ignore

        return openroad
    except ImportError:
        return None


def dump_feature_maps(design: Any, grid: int = 128) -> dict:
    """
    Conceptual: rasterize density / pin / RUDY / power into HxW grids from OpenDB.
    """
    if try_import_openroad() is None or design is None:
        return {"status": "stub", "grid": grid}
    return {"status": "openroad-present", "grid": grid}


def suggest_density_padding(cong_map) -> float:
    """Map predicted congestion peak → ORFS CORE_UTIL / padding hint."""
    try:
        peak = float(cong_map.max())
    except Exception:
        peak = 0.0
    return min(0.2, max(0.0, (peak - 0.5) * 0.3))
