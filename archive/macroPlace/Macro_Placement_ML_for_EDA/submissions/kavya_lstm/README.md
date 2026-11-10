# Kavya LSTM Macro Placer — Challenge Submission

Based on the `train_all_LSTM` branch: GAT encoder + LSTM pointer network for macro ordering, plus wirelength-driven placement, legalization, and SA refinement.

## Run (from challenge repo root)

```bash
git submodule update --init external/MacroPlacement
uv sync
uv run evaluate submissions/kavya_lstm/placer.py -b ibm01
uv run evaluate submissions/kavya_lstm/placer.py --all
```

## Layout

| File | Role |
|------|------|
| `placer.py` | Entry point (`KavyaLSTMPlacer.place`) |
| `placement_engine.py` | Ordering + placement + SA |
| `benchmark_adapter.py` | `Benchmark` → graph tensors |
| `legalize.py` | Zero-overlap legalization |
| `maskplace/` | LSTM + GAT model code |
| `weights/` | Optional checkpoints |

## License

Apache 2.0 (align with competition requirement for winners).

## Team

Macro_Placement_ML_for_EDA / `train_all_LSTM`
