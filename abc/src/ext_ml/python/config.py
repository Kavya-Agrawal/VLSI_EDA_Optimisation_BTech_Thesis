"""SYNAPSE shared configuration.

This file is the Python-side mirror of ``ml_abc.h``. The feature dimensions
MUST match the C extractor exactly, otherwise the ONNX model fed to ABC will
read garbage. See ``docs/DESIGN.md`` section 4.
"""

from dataclasses import dataclass, field
from typing import List

# --- feature dimensions (keep in sync with ml_abc.h) -----------------------
NODE_FEAT_DIM: int = 16   # per-node structural + functional features
DIV_FEAT_DIM: int = 12    # per-candidate (divisor/cut/window) pair features
EDGE_ATTR_DIM: int = 1    # per-edge attribute (fanin complement bit)
EMB_DIM: int = 64         # encoder embedding width

# --- task ids (keep in sync with Ml_Task_t in ml_abc.h) --------------------
TASK_POTENTIAL: int = 0
TASK_RESUB_DIV: int = 1
TASK_MFS_WINDOW: int = 2
TASK_CUT_RANK: int = 3

# Human-readable names for the 16 node features (documentation / debugging).
NODE_FEATURE_NAMES: List[str] = [
    "level_norm", "revlevel_norm", "fanout_log", "fanin0_compl", "fanin1_compl",
    "fanin0_is_ci", "fanin1_is_ci", "mffc_log", "po_fanout_frac", "level_slack",
    "dist_to_pi", "r2_density", "fanout_compl_frac", "on_critical_path",
    "reconvergence", "bias",
]


@dataclass
class SynapseConfig:
    node_feat_dim: int = NODE_FEAT_DIM
    div_feat_dim: int = DIV_FEAT_DIM
    edge_attr_dim: int = EDGE_ATTR_DIM
    emb_dim: int = EMB_DIM

    # encoder
    encoder: str = "aigconv"          # one of: gcn | sage | gat | aigconv
    n_layers: int = 4
    prop_steps: int = 3               # AIGConv reversible propagation rounds
    dropout: float = 0.1
    gat_heads: int = 4

    # heads
    head_hidden: int = 128

    # training
    lr: float = 1e-3
    weight_decay: float = 1e-5
    epochs: int = 50
    batch_size: int = 16
    gamma: float = 0.9                # discount for non-myopic potential returns

    # multi-task loss weights
    w_potential: float = 1.0
    w_rank: float = 1.0
    w_policy: float = 0.5

    device: str = "cuda"              # falls back to cpu automatically in scripts

    def rank_input_dim(self) -> int:
        # [root_emb || cand_emb || pair_feats]
        return 2 * self.emb_dim + self.div_feat_dim
