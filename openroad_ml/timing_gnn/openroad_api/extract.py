"""Optional live OpenROAD feature extraction (stubs — works without build)."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Any


@dataclass
class ExtractedGraph:
    n_nodes: int
    n_edges: int
    note: str


def try_import_openroad():
    try:
        import openroad  # type: ignore

        return openroad
    except ImportError:
        return None


def extract_timing_graph(design: Any = None) -> ExtractedGraph:
    """
    When OpenROAD Python is available:
      - iterate instances / nets from design.getBlock()
      - pull liberty / fanout / approx capacitance
      - optionally query OpenSTA arrivals

    Without OpenROAD, returns a stub describing the expected schema.
    """
    ora = try_import_openroad()
    if ora is None or design is None:
        return ExtractedGraph(
            n_nodes=0,
            n_edges=0,
            note="stub: build OpenROAD with Python bindings, then pass Design",
        )
    # Placeholder for real extraction — keep schema stable for trainers.
    return ExtractedGraph(n_nodes=0, n_edges=0, note="openroad present; wire extraction here")
