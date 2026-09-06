# Research Notes

The framework follows a conservative pattern from recent algorithm-evolution work: evolve a small executable fragment, evaluate it with a real compiler and real workloads, preserve rejected attempts, and separate training from held-out checks.

## Papers mapped into the design

- **AlphaEvolve**, Novikov et al., Google DeepMind, 2025. The key idea used here is an executable-code loop with automated correctness checks before objective scoring.
- **Autonomous Evolution of EDA Tools: Multi-Agent Self-Evolved ABC**, Cunxi Yu and Haoxing Ren, 2026. This motivates keeping compile correctness and QoR checks inside the loop for real EDA tool source.
- **VPR-Evolve**, Qihang Wu, Taizun Jafri, Aman Arora and Vidya A. Chhabria, 2026. This motivates fixed baselines, train/validation/test splits, repeated runs and rejected-history tracking.
- **EvoDRC**, Bing-Yue Wu, Chia-Tung Ho, Haoyu Yang, Brucek Khailany and Vidya A. Chhabria, 2026. This motivates bounded physical-design edits plus strict connectivity and DRC checks.
- **FunSearch**, Romera-Paredes et al., Nature, 2023, and **EoH**, Liu et al., ICML 2024. These motivate evolving compact heuristics instead of asking a model to rewrite a large system.

## Implemented OpenROAD target

The implemented target is the setup path-driver repair ordering in OpenROAD resizer. The stock code ranks candidate drivers by load delay after collecting the critical path and latch fanin context. The patch inserts a generated policy after stock candidate collection, then reorders only those existing candidates. The policy cannot create, delete or mutate timing objects.

Candidate features:

- `load`: normalized load delay from the stock target ranking.
- `fanout`: normalized driver fanout.
- `position`: normalized original rank position in the stock ordering.

Candidate expression grammar:

- Features: `load`, `fanout`, `position`
- Operators: `add`, `sub`, `mul`, `min`, `max`
- Constants: finite values in `[-4, 4]`
- Limits: depth 5, 31 nodes, 8 KiB policy file

## Scoring contract

The objective is paired setup timing improvement:

```text
0.5 * delta(setup WNS) / period
+ 0.5 * delta(setup TNS) / (period * constrained endpoints)
```

Every candidate must also pass hold timing non-regression, zero physical/electrical violations, formal equivalence and independent STA audit. Area, wirelength and runtime have bounded regression caps.

Clock tree distribution enters the evidence contract through setup and hold skew audit metrics. CTS algorithm evolution remains future work because it needs a separate bounded mutation target and additional clock topology invariants.
