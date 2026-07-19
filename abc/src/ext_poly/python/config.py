"""POLYPHONY shared config (mirrors poly_abc.h)."""

POLY_MAX_VARS = 6
POLY_MAX_GATES = 32
POLY_MAX_PROGRAMS = 16

# Token vocab for the generator:
#   GATE: emit (lit_a, lit_b)
#   OUT:  emit output literal
# Literals are integers in [0, 2*(nVars+nGates)).

class PolyConfig:
    max_vars = POLY_MAX_VARS
    max_gates = POLY_MAX_GATES
    d_model = 128
    n_heads = 4
    n_layers = 3
    dropout = 0.1
    lr = 1e-3
    batch_size = 32
    alpha_size = 0.3      # reward size penalty
    beta_novelty = 0.5    # reward novelty bonus
    device = "cpu"
