"""GAT encoder + LSTM pointer decoder for macro ordering."""

import torch
import torch.nn as nn
import torch.nn.functional as F


class GATLayer(nn.Module):
    def __init__(self, in_dim, out_dim, heads=4):
        super().__init__()
        self.heads = heads
        self.out_dim = out_dim // heads

        self.W = nn.Linear(in_dim, out_dim, bias=False)
        self.attn_l = nn.Parameter(torch.Tensor(1, heads, self.out_dim))
        self.attn_r = nn.Parameter(torch.Tensor(1, heads, self.out_dim))
        self.leaky_relu = nn.LeakyReLU(0.2)

        nn.init.xavier_uniform_(self.W.weight)
        nn.init.xavier_uniform_(self.attn_l)
        nn.init.xavier_uniform_(self.attn_r)

    def forward(self, x, adj):
        n = x.size(0)
        h = self.W(x).view(n, self.heads, self.out_dim)

        a_l = (h * self.attn_l).sum(dim=-1, keepdim=True)
        a_r = (h * self.attn_r).sum(dim=-1, keepdim=True)

        a_l = a_l.permute(0, 2, 1)
        a_r_t = a_r.permute(2, 0, 1)

        score = self.leaky_relu(a_l + a_r_t)
        mask = (adj == 0).unsqueeze(-1)
        score = score.masked_fill(mask, -1e9)

        attn = F.softmax(score, dim=1)
        h_prime = torch.einsum("njh,jhd->nhd", attn, h)
        return h_prime.reshape(n, -1)


class GNNEncoder(nn.Module):
    def __init__(self, in_dim=4, hidden_dim=128):
        super().__init__()
        self.layer1 = GATLayer(in_dim, hidden_dim)
        self.layer2 = GATLayer(hidden_dim, hidden_dim)
        self.layer3 = GATLayer(hidden_dim, hidden_dim)
        self.norm = nn.LayerNorm(hidden_dim)

    def forward(self, x, adj):
        adj = adj + torch.eye(adj.size(0), device=adj.device)
        h = F.elu(self.layer1(x, adj))
        h = F.elu(self.layer2(h, adj)) + h
        h = self.layer3(h, adj) + h
        return self.norm(h)


class PointerDecoder(nn.Module):
    def __init__(self, hidden_dim=128):
        super().__init__()
        self.lstm = nn.LSTMCell(hidden_dim, hidden_dim)
        self.W_q = nn.Linear(hidden_dim, hidden_dim)
        self.W_k = nn.Linear(hidden_dim, hidden_dim)
        self.v = nn.Linear(hidden_dim, 1)

    def forward(self, embeddings):
        n, d = embeddings.shape
        device = embeddings.device

        mask = torch.zeros(n, device=device)
        selected_indices = []
        log_probs = []

        h = torch.zeros(1, d, device=device)
        c = torch.zeros(1, d, device=device)
        inp = embeddings.mean(dim=0, keepdim=True)

        for _ in range(n):
            h, c = self.lstm(inp, (h, c))
            query = self.W_q(h)
            keys = self.W_k(embeddings)
            scores = self.v(torch.tanh(query + keys)).squeeze(-1)
            masked_scores = scores + mask
            probs = F.softmax(masked_scores, dim=0)
            dist = torch.distributions.Categorical(probs)
            idx = dist.sample()
            log_probs.append(dist.log_prob(idx))
            selected_indices.append(idx.item())
            mask[idx] = -1e9
            inp = embeddings[idx].unsqueeze(0)

        return selected_indices, torch.stack(log_probs).sum()


class PointerOrderingModel(nn.Module):
    def __init__(self, in_dim=4, hidden_dim=128):
        super().__init__()
        self.encoder = GNNEncoder(in_dim, hidden_dim)
        self.decoder = PointerDecoder(hidden_dim)

    def forward(self, x, adj):
        embeddings = self.encoder(x, adj)
        return self.decoder(embeddings)
