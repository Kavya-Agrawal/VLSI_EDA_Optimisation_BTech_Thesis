# Model weights

Copy your trained LSTM ordering checkpoint from `train_all_LSTM` into this folder.

Supported filenames (first match wins):

- `ordering_lstm.pth`
- `model_best.pth`
- `model_best_adaptec4.pth`

The file must be a `torch.save` state dict compatible with `PointerOrderingModel`.

If no checkpoint is present, the placer uses connectivity-based ordering only (still legal, slower to optimize proxy cost).

**Recommended:** Fine-tune on IBM benchmarks (`ibm01`–`ibm18`) and save as `ordering_lstm.pth`.
