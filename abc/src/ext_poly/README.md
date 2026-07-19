# POLYPHONY

Diverse generative synthesis of equivalent subcircuits for choice-based mapping in Berkeley ABC.

## What / why
Exact multi-level synthesis is **NP-hard**. Prior neural work (Circuit Transformer, ShortCircuit) generates **one** circuit. ABC's best mapping wants a **diverse set of equivalents** ("choices"). POLYPHONY learns / proposes that distribution; every candidate is **exactly verified** against the truth table.

## Docs
- `docs/NP_HARD_HOTSPOTS.md` — full list of NP-hard/heuristic spots in ABC
- `docs/DESIGN.md` — architecture + novelty
- `docs/INTEGRATION.md` — build + commands
- `docs/STATUS.md` — done vs stubbed

## Quick try (after `make` in `abc/`)
```
./abc -c "&r file.aig; poly_extract -N 5"
./abc -c "poly_synth -K 3; poly_stats"
```

## Python (no ABC build needed)
```
cd abc/src/ext_poly/python
python -m tests.test_smoke
python -m train.train_gflownet --mode demo --n-vars 3
```
