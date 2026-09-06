# Verification Contract

The evaluator treats performance as invalid unless correctness evidence also passes.

## Candidate build gates

1. Parse policy JSON with exact keys.
2. Generate `EvolvedPathDriverPolicy.h` from a bounded expression grammar.
3. Compile the actual generated header under ASan and UBSan.
4. Differential-test the C++ ranking against the Python reference on randomized feature vectors.
5. Patch a pinned OpenROAD checkout and verify the exact fixed source diff.
6. Build OpenROAD in the pinned Docker image.
7. Run the selected upstream resizer regression tests.

## Flow evidence gates

Each design and replica run must produce final ORFS artifacts:

- `1_1_yosys.v`
- `6_final.v`
- `6_final.odb`
- `6_final.sdc`
- `6_final.spef`
- `6_final.gds`

The run then performs an independent audit with a frozen stock OpenROAD binary. The audit checks timing, constraints, placement legality, antenna metrics, design-rule metrics, clock period, endpoint count and clock skew.

## Fail-closed rules

The candidate is rejected when:

- Any required metric is missing, boolean-like, nonnumeric, nonfinite or physically impossible.
- Any setup or hold WNS/TNS metric regresses against the paired baseline.
- Any placement, routing DRC, antenna, max slew, max capacitance or max fanout count is nonzero.
- Area, wirelength or runtime exceed configured caps.
- Candidate, evaluator, protocol or audit binary hashes change during the run.
- The train/validation/test matrix is incomplete, duplicated or mixed across candidate IDs.

## Limitations

This framework validates single-corner Nangate45 ORFS runs in the configured smoke campaign. It is not a signoff MCMM closure flow, and it does not claim CTS optimization until a separate CTS mutation target and clock topology checker are added.
