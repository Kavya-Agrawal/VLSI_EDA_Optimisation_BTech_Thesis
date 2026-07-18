"""Loaders for the two data artifacts produced by the ABC C side.

1. GIA feature dumps  (``ml_features -o file``) -> per-circuit graph tensors.
   Format (text):
       NODES <n> <feat_dim>
       <id> f0 ... f{d-1}      (n lines)
       EDGES <m>
       <src> <dst> <compl>     (m lines)

2. Decision CSVs      (``ml_config -c file.csv``) -> per-candidate rows.
   Format: ``task,label,feat0,feat1,...``
"""

from __future__ import annotations

import os
from typing import List

import numpy as np

try:
    import torch
    from torch.utils.data import Dataset
except Exception:  # pragma: no cover
    torch = None
    Dataset = object


def load_gia_graph(path: str):
    """Parse a GIA feature dump into (x, edge_index, edge_attr, id_map)."""
    with open(path, "r") as fh:
        header = fh.readline().split()
        assert header[0] == "NODES", f"bad header in {path}"
        n, d = int(header[1]), int(header[2])
        ids: List[int] = []
        feats = np.zeros((n, d), dtype=np.float32)
        for i in range(n):
            parts = fh.readline().split()
            ids.append(int(parts[0]))
            feats[i] = np.asarray(parts[1:1 + d], dtype=np.float32)
        id_map = {gid: i for i, gid in enumerate(ids)}
        eh = fh.readline().split()
        assert eh[0] == "EDGES", f"bad edge header in {path}"
        m = int(eh[1])
        src, dst, attr = [], [], []
        for _ in range(m):
            s, t, c = fh.readline().split()
            s, t = int(s), int(t)
            # keep only edges whose endpoints are AND rows we have features for
            if s in id_map and t in id_map:
                src.append(id_map[s]); dst.append(id_map[t]); attr.append([float(c)])
    if torch is None:
        return feats, (np.asarray(src), np.asarray(dst)), np.asarray(attr), id_map
    x = torch.from_numpy(feats)
    edge_index = torch.tensor([src, dst], dtype=torch.long)
    edge_attr = torch.tensor(attr, dtype=torch.float32) if attr else torch.zeros((0, 1))
    return x, edge_index, edge_attr, id_map


class DecisionCSV(Dataset):
    """Per-candidate rows for supervised ranker / potential / window training."""

    def __init__(self, path: str, task: int | None = None):
        rows = []
        with open(path, "r") as fh:
            for line in fh:
                if not line or line.startswith("#"):
                    continue
                parts = line.strip().split(",")
                if len(parts) < 3:
                    continue
                t = int(parts[0])
                if task is not None and t != task:
                    continue
                label = float(parts[1])
                feats = np.asarray(parts[2:], dtype=np.float32)
                rows.append((t, label, feats))
        self.rows = rows

    def __len__(self):
        return len(self.rows)

    def __getitem__(self, i):
        t, label, feats = self.rows[i]
        if torch is None:
            return t, label, feats
        return t, torch.tensor(label), torch.from_numpy(feats)


def load_graph_dir(dir_path: str):
    """Load every *.txt GIA dump in a directory."""
    graphs = []
    for fn in sorted(os.listdir(dir_path)):
        if fn.endswith(".txt"):
            graphs.append(load_gia_graph(os.path.join(dir_path, fn)))
    return graphs
