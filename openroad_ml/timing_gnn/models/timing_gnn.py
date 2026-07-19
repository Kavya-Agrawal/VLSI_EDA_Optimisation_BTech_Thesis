"""Timing GNN: net-delay and endpoint-slack prediction."""

from __future__ import annotations

from dataclasses import dataclass

import torch
import torch.nn as nn
import torch.nn.functional as F


@dataclass
class TimingGNNConfig:
    node_dim: int = 16
    edge_dim: int = 8
    hidden: int = 64
    layers: int = 3
    dropout: float = 0.1


class GraphConv(nn.Module):
    """Simple mean-aggregation message passing (no torch_geometric required)."""

    def __init__(self, in_dim: int, out_dim: int, edge_dim: int):
        super().__init__()
        self.msg = nn.Linear(in_dim + edge_dim, out_dim)
        self.upd = nn.Linear(in_dim + out_dim, out_dim)
        self.norm = nn.LayerNorm(out_dim)

    def forward(
        self,
        x: torch.Tensor,
        edge_index: torch.Tensor,
        edge_attr: torch.Tensor,
    ) -> torch.Tensor:
        # x: [N, F], edge_index: [2, E], edge_attr: [E, Fe]
        src, dst = edge_index[0], edge_index[1]
        m = self.msg(torch.cat([x[src], edge_attr], dim=-1))
        agg = torch.zeros(x.size(0), m.size(-1), device=x.device, dtype=x.dtype)
        agg.index_add_(0, dst, m)
        deg = torch.zeros(x.size(0), 1, device=x.device, dtype=x.dtype)
        deg.index_add_(0, dst, torch.ones(dst.size(0), 1, device=x.device, dtype=x.dtype))
        agg = agg / deg.clamp(min=1.0)
        return self.norm(F.relu(self.upd(torch.cat([x, agg], dim=-1))))


class TimingGNN(nn.Module):
    def __init__(self, cfg: TimingGNNConfig | None = None):
        super().__init__()
        self.cfg = cfg or TimingGNNConfig()
        c = self.cfg
        self.node_enc = nn.Linear(c.node_dim, c.hidden)
        self.edge_enc = nn.Linear(c.edge_dim, c.edge_dim)
        self.convs = nn.ModuleList(
            [GraphConv(c.hidden, c.hidden, c.edge_dim) for _ in range(c.layers)]
        )
        self.drop = nn.Dropout(c.dropout)
        self.net_delay_head = nn.Sequential(
            nn.Linear(c.hidden * 2 + c.edge_dim, c.hidden),
            nn.ReLU(),
            nn.Linear(c.hidden, 1),
        )
        self.slack_head = nn.Sequential(
            nn.Linear(c.hidden, c.hidden),
            nn.ReLU(),
            nn.Linear(c.hidden, 1),
        )

    def encode(
        self,
        x: torch.Tensor,
        edge_index: torch.Tensor,
        edge_attr: torch.Tensor,
    ) -> tuple[torch.Tensor, torch.Tensor]:
        h = F.relu(self.node_enc(x))
        e = F.relu(self.edge_enc(edge_attr))
        for conv in self.convs:
            h = self.drop(conv(h, edge_index, e))
        return h, e

    def forward(
        self,
        x: torch.Tensor,
        edge_index: torch.Tensor,
        edge_attr: torch.Tensor,
        endpoint_mask: torch.Tensor | None = None,
    ) -> dict[str, torch.Tensor]:
        h, e = self.encode(x, edge_index, edge_attr)
        src, dst = edge_index[0], edge_index[1]
        net_feat = torch.cat([h[src], h[dst], e], dim=-1)
        net_delay = self.net_delay_head(net_feat).squeeze(-1)
        slack = self.slack_head(h).squeeze(-1)
        if endpoint_mask is not None:
            slack = slack * endpoint_mask.float()
        return {"net_delay": net_delay, "slack": slack, "node_emb": h}


def analytic_fallback_slack(x: torch.Tensor) -> torch.Tensor:
    """No-torch-weights baseline: negative weighted fanout proxy."""
    # features assumed: [:, 0]=fanout_norm, [:, 1]=load_norm
    return -(x[:, 0] + 0.5 * x[:, 1])
