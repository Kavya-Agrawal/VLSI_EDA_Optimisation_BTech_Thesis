# A Deep Reinforcement Learning Approach for Global Routing

- **Authors:** Haiguang Liao, Wentai Zhang, Xuliang Dong, Barnabas Poczos, Kenji Shimada, Levent Burak Kara (Carnegie Mellon)
- **Venue / Year:** **J. Mechanical Design 2019**
- **PDF:** `DeepRL_GlobalRouting_2019.pdf`
- **Link:** https://arxiv.org/abs/1906.08809

---

## TL;DR (one breath)
Frames **global routing** (connecting placed pins with wires through a grid, without over-using capacity) as an RL problem: an agent learns to route nets one by one on a 3D grid graph, using a **Deep Q-Network (DQN)**. An early proof-of-concept that RL can route.

## The problem (plain English)
After placement, **routing** connects all the pins with wires. **Global routing** does this coarsely on a grid of "tiles," where each edge has a **capacity** (how many wires can cross). The goal: connect everything with **short wires** and **no capacity overflow**. It's a huge combinatorial problem.

## Key idea — routing as sequential decisions
Model the routing grid as a graph. For each net, an RL **agent walks the grid** choosing directions (up/down/left/right/via) to connect pins, learning a policy that avoids congestion and minimizes wirelength.

## How it works
1. Build a **grid graph** with edge capacities.
2. **DQN agent**: state = current position + local capacity/target info; actions = moves on the grid; reward encourages reaching the target with short, non-overflowing paths.
3. A **conjoint / curriculum** setup helps the agent handle many nets.

## Results
- Demonstrates RL can solve global-routing problem instances, **competitive with a standard A\*-search router** on their benchmarks.
- Proof-of-concept: routing quality improves with learning.

## Why it matters for your BTP
- The **canonical "RL-for-routing"** reference — good background for the routing domain and for **joint place-and-route** ideas (see DeepPR).
- Shows the grid-graph + capacity formulation you'll see reused everywhere in routing ML.

## Limitations
- Small-scale vs modern industrial designs.
- DQN is dated; scalability to millions of nets is unproven here.
- Classic routers remain strong baselines.

## Mini-glossary
- **Global routing:** coarse, grid-level wire planning (vs *detailed routing* = exact tracks).
- **Capacity / overflow:** how many wires an edge allows / how much you exceed it.
- **DQN:** Deep Q-Network — value-based RL for discrete actions.
- **Via:** a vertical connection between metal layers.
