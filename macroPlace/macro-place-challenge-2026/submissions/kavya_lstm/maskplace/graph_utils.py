"""Build macro connectivity graph for GNN + LSTM ordering."""

import torch


def build_graph(node_info, node_to_net_dict, device):
    node_names = list(node_info.keys())
    n = len(node_names)
    name_to_idx = {name: i for i, name in enumerate(node_names)}

    areas = [node_info[n]["x"] * node_info[n]["y"] for n in node_names]
    widths = [node_info[n]["x"] for n in node_names]
    heights = [node_info[n]["y"] for n in node_names]
    degrees = [len(node_to_net_dict[n]) for n in node_names]

    max_area = max(areas) if areas else 1.0
    max_w = max(widths) if widths else 1.0
    max_h = max(heights) if heights else 1.0
    max_deg = max(degrees) if degrees else 1

    features = []
    for name in node_names:
        area = (node_info[name]["x"] * node_info[name]["y"]) / max_area
        deg = len(node_to_net_dict[name]) / max_deg
        w = node_info[name]["x"] / max_w
        h = node_info[name]["y"] / max_h
        features.append([area, deg, w, h])

    x = torch.tensor(features, dtype=torch.float32, device=device)
    adj = torch.zeros((n, n), device=device)

    net_to_nodes = {}
    for node, nets in node_to_net_dict.items():
        for net in nets:
            net_to_nodes.setdefault(net, []).append(node)

    for nodes in net_to_nodes.values():
        idxs = [name_to_idx[node] for node in nodes]
        for i in idxs:
            for j in idxs:
                adj[i, j] = 1.0

    deg = adj.sum(dim=1, keepdim=True) + 1e-6
    adj = adj / deg

    return x, adj, node_names
