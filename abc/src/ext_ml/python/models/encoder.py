"""SYNAPSE AIG encoders.

Four interchangeable backbones map an AIG (nodes + fanin edges) to a per-node
embedding of width ``cfg.emb_dim``. Pick one via ``cfg.encoder``.

    gcn      - vanilla GCN (topology-only baseline)
    sage     - GraphSAGE (inductive; generalizes to unseen circuits)
    gat      - graph attention (learns which fanins matter)
    aigconv  - custom DeepGate-style layer that respects AIG semantics
               (separate fanin aggregation, complement-aware gating, GRU
               state update, forward+backward reversible propagation).

`aigconv` is the recommended encoder; the others are provided for ablations.
"""

from __future__ import annotations

import torch
import torch.nn as nn
import torch.nn.functional as F

try:  # torch_geometric is only needed for gcn/sage/gat backbones
    from torch_geometric.nn import GCNConv, SAGEConv, GATConv
    _HAS_PYG = True
except Exception:  # pragma: no cover - optional dependency
    _HAS_PYG = False


class _MLP(nn.Module):
    def __init__(self, din, dhid, dout):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(din, dhid), nn.ReLU(), nn.Linear(dhid, dout)
        )

    def forward(self, x):
        return self.net(x)


class AIGConvEncoder(nn.Module):
    """DeepGate-style message passing tailored to And-Inverter Graphs.

    Each node has exactly two fanins (for AND nodes) with a complement bit per
    edge. We aggregate the two (optionally inverted) fanin messages, update a
    hidden state with a GRU cell, and repeat for ``prop_steps`` rounds in the
    forward (PI->PO) direction, then the same backward, giving each node a
    receptive field that spans both its transitive fan-in and fan-out.
    """

    def __init__(self, cfg):
        super().__init__()
        self.cfg = cfg
        d = cfg.emb_dim
        self.in_proj = nn.Linear(cfg.node_feat_dim, d)
        self.msg = _MLP(d + cfg.edge_attr_dim, cfg.head_hidden, d)
        self.gru = nn.GRUCell(d, d)
        self.out = nn.Linear(d, d)

    def _propagate(self, h, edge_index, edge_attr):
        # edge_index: [2, E] with row 0 = src (fanin), row 1 = dst (node)
        src, dst = edge_index[0], edge_index[1]
        m_in = torch.cat([h[src], edge_attr], dim=-1)
        m = self.msg(m_in)                       # message per edge
        agg = torch.zeros_like(h)
        agg.index_add_(0, dst, m)                # sum messages into destination
        return self.gru(agg, h)                  # state update

    def forward(self, x, edge_index, edge_attr):
        h = torch.tanh(self.in_proj(x))
        rev = torch.stack([edge_index[1], edge_index[0]], dim=0)
        for _ in range(self.cfg.prop_steps):
            h = self._propagate(h, edge_index, edge_attr)      # forward
            h = self._propagate(h, rev, edge_attr)             # backward
        return self.out(h)


class _PygEncoder(nn.Module):
    """Wrapper for the standard PyG convolutions (gcn / sage / gat)."""

    def __init__(self, cfg):
        super().__init__()
        if not _HAS_PYG:
            raise ImportError(
                "torch_geometric is required for the gcn/sage/gat encoders; "
                "use encoder='aigconv' or install torch_geometric."
            )
        d = cfg.emb_dim
        self.in_proj = nn.Linear(cfg.node_feat_dim, d)
        self.layers = nn.ModuleList()
        for _ in range(cfg.n_layers):
            if cfg.encoder == "gcn":
                self.layers.append(GCNConv(d, d))
            elif cfg.encoder == "sage":
                self.layers.append(SAGEConv(d, d))
            elif cfg.encoder == "gat":
                heads = cfg.gat_heads
                self.layers.append(GATConv(d, d // heads, heads=heads))
            else:
                raise ValueError(f"unknown encoder {cfg.encoder}")
        self.dropout = cfg.dropout

    def forward(self, x, edge_index, edge_attr=None):
        h = torch.relu(self.in_proj(x))
        for conv in self.layers:
            h = conv(h, edge_index)
            h = F.relu(h)
            h = F.dropout(h, p=self.dropout, training=self.training)
        return h


def build_encoder(cfg):
    if cfg.encoder == "aigconv":
        return AIGConvEncoder(cfg)
    return _PygEncoder(cfg)
