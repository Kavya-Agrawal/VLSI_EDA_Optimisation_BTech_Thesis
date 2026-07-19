"""OpenROAD hooks for live gate sizing (stubs without a local build)."""

from __future__ import annotations

from typing import Any


def try_import_openroad():
    try:
        import openroad  # type: ignore

        return openroad
    except ImportError:
        return None


def swap_master(design: Any, inst_name: str, master_name: str) -> bool:
    """
    Live path (conceptual):
      inst = block.findInst(inst_name)
      master = db.findMaster(master_name)
      inst.swapMaster(master)
      design.getSta().updateTiming()
    """
    if try_import_openroad() is None or design is None:
        return False
    return False  # wire real API when OpenROAD is linked


def read_tns_wns(design: Any) -> tuple[float, float]:
    if try_import_openroad() is None or design is None:
        return 0.0, 0.0
    return 0.0, 0.0
