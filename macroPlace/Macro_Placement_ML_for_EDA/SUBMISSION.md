# Macro Placement Challenge — Submission Guide

## What was added

`submissions/kavya_lstm/` is a **challenge-ready** placer package derived from `train_all_LSTM`:

- Implements `place(benchmark) -> Tensor` for the Partcl evaluator
- Does **not** import `PPO2.py` or `gym` at runtime (faster, fewer deps)
- Uses LSTM ordering when weights exist in `submissions/kavya_lstm/weights/`

## Submit to judges

1. Clone https://github.com/partcleda/macro-place-challenge-2026
2. Copy this folder into the challenge repo:

   ```powershell
   Copy-Item -Recurse -Force `
     "submissions\kavya_lstm" `
     "..\macro-place-challenge-2026\submissions\kavya_lstm"
   ```

3. Initialize submodule and test:

   ```powershell
   cd ..\macro-place-challenge-2026
   git submodule update --init external/MacroPlacement
   uv sync
   uv run evaluate submissions/kavya_lstm/placer.py --all
   ```

4. Push a repo the judges can access and fill https://forms.gle/YDRtYV5Vq68SZgKW9

## Improve scores

- Train/fine-tune `PointerOrderingModel` on IBM `ibm01`–`ibm18`
- Save as `submissions/kavya_lstm/weights/ordering_lstm.pth`
- Re-run `--all` and confirm **0 overlaps** and runtime **< 1 hour/benchmark**
