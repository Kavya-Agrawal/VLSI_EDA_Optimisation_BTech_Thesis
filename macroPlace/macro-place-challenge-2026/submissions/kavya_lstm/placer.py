"""
Macro Placement Challenge 2026 — LSTM ordering + wirelength placement.

Entry point for judges:
    uv run evaluate submissions/kavya_lstm/placer.py --all

Place trained weights in submissions/kavya_lstm/weights/ (see weights/README.md).
"""

from __future__ import annotations

import sys
from pathlib import Path

# Ensure submission directory is on path for local imports
_SUBMISSION_ROOT = Path(__file__).resolve().parent
if str(_SUBMISSION_ROOT) not in sys.path:
    sys.path.insert(0, str(_SUBMISSION_ROOT))

import torch
from macro_place.benchmark import Benchmark

from placement_engine import place_hard_macros


class KavyaLSTMPlacer:
    """
    Hard-macro placer using GAT + LSTM macro ordering (train_all_LSTM branch)
    followed by connectivity-aware placement, legalization, and SA refinement.
    """

    def __init__(self, seed: int = 42, order_samples: int = 5, sa_iters: int = 2500):
        self.seed = seed
        self.order_samples = order_samples
        self.sa_iters = sa_iters
        self.weights_dir = _SUBMISSION_ROOT / "weights"

    def place(self, benchmark: Benchmark) -> torch.Tensor:
        torch.manual_seed(self.seed)
        return place_hard_macros(
            benchmark,
            weights_dir=self.weights_dir,
            seed=self.seed,
            order_samples=self.order_samples,
            sa_iters=self.sa_iters,
        )


# Alias for evaluate harness (first class with place() method)
MacroPlacementLSTMPlacer = KavyaLSTMPlacer
