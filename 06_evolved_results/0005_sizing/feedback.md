# Feedback for iteration 5 (0005_sizing, cluster sizing)

```
vs champion:
REJECT  score=+0.00000
  nangate45/gcd      WNS -0.1742 -> -0.1742 ns  TNS -7.626 -> -7.626 ns  score +0.00000
  nangate45/aes      WNS -0.1083 -> -0.1083 ns  TNS -14.773 -> -14.773 ns  score +0.00000
  nangate45/ibex     WNS -0.2994 -> -0.2994 ns  TNS -416.273 -> -416.273 ns  score +0.00000
  ! score +0.00000 below required gain +0.00200

vs baseline:
ACCEPT  score=+0.00000
  nangate45/gcd      WNS -0.1742 -> -0.1742 ns  TNS -7.626 -> -7.626 ns  score +0.00000
  nangate45/aes      WNS -0.1083 -> -0.1083 ns  TNS -14.773 -> -14.773 ns  score +0.00000
  nangate45/ibex     WNS -0.2994 -> -0.2994 ns  TNS -416.273 -> -416.273 ns  score +0.00000
```

Cannot save `feedback.md`: this session’s filesystem permissions are read-only. Completed content follows.

# 1. Outcome

**REJECT versus champion.** Score **+0.00000**, below the required **+0.00200**. Baseline verdict is **ACCEPT at parity**, with no measured improvement.

Deltas are candidate minus reference; positive timing deltas indicate improvement. Champion and baseline values are identical.

| Design | Reference → candidate WNS (ns) | ΔWNS (ns) | Reference → candidate TNS (ns) | ΔTNS (ns) |
|---|---:|---:|---:|---:|
| nangate45/gcd | -0.1742 → -0.1742 | 0.00000 | -7.626 → -7.626 | 0.00000 |
| nangate45/aes | -0.1083 → -0.1083 | 0.00000 | -14.773 → -14.773 | 0.00000 |
| nangate45/ibex | -0.2994 → -0.2994 | 0.00000 | -416.273 → -416.273 | 0.00000 |

Both replicates produced identical timing for each design. All six unit targets and ten smoke tests passed. API compatibility is no longer the blocker; timing effectiveness is.

# 2. Did the hypothesis do what it predicted?

**No measured incremental effect.**

The patch in `src/move/SizeUpGenerator.cc` checks `replacementPreservesMaxCap` before an improving contender updates the best score. The protected `upsizeCell` signature remains intact through a library-only wrapper; production generation supplies instance context and still emits at most one candidate.

Predicted evidence was recovered feasible replacements, changed drive strengths, and lower matched AES/Ibex data arrivals without additional logic stages. Observed reference comparisons show **zero improved, zero regressed, zero newly listed, and zero removed paths in every design**. No incremental arrival reduction or depth benefit is demonstrated.

AES’s implementation target was ΔWNS ≥ **+0.005 ns** and at least **1% lower TNS magnitude**—approximately **0.148 ns** less negative TNS. Both measured deltas are zero.

Pre/post-repair gains belong to the complete repair flow and are also achieved by the reference. For example, AES `sa23_sr[0]$_DFF_P_/D` improves by **0.040944 ns** during repair; this is not evidence for the new selection rule.

The available logs do not count suppressed winners, feasible runner-ups, or committed recoveries. Therefore, zero opportunities cannot be established: opportunities could be absent, rejected later, or timing-neutral. Reject the mechanism for promotion on tier A; its proposed causal explanation remains unverified.

# 3. Where the remaining negative slack comes from

The five worst reported endpoints across designs are all in Ibex.

| Endpoint | Slack (ns) | Stages / maximum fanout | Likely cause | Moves that should address it; likely limitation |
|---|---:|---:|---|---|
| `gen_regfile_ff.register_file_i.rf_reg[703]$_DFFE_PN0P_/D` | -0.299412 | 35 / 943 | High fanout, weak reported driver, deep logic | Buffering, load splitting, cloning, selective sizing. Master selection alone cannot partition the shared load or shorten the logic cone. |
| `gen_regfile_ff.register_file_i.rf_reg[607]$_DFFE_PN0P_/D` | -0.299021 | 35 / 943 | Same shared bottleneck | Split critical sinks from noncritical load; existing move eligibility, ordering, or acceptance may leave the bottleneck intact. |
| `gen_regfile_ff.register_file_i.rf_reg[831]$_DFFE_PN0P_/D` | -0.298793 | 35 / 943 | Same shared bottleneck | Clone or buffer the shared driver with upstream-loading checks. Feasible-runner-up ranking creates no new topology. |
| `gen_regfile_ff.register_file_i.rf_reg[799]$_DFFE_PN0P_/D` | -0.298775 | 35 / 943 | Same shared bottleneck | Criticality-aware buffering/load splitting; local sizing gain may be exhausted before shared-load relief occurs. |
| `gen_regfile_ff.register_file_i.rf_reg[895]$_DFFE_PN0P_/D` | -0.298720 | 35 / 943 | Same shared bottleneck | Load isolation first; logic restructuring if cell-delay decomposition confirms depth dominates afterward. |

All five list `AND2_X1@_26153_/ZN` as the worst-slew driver and `AOI221_X2@_22445_/ZN` second. Reported slew values are **2087753088.0** and **57608004.0**, respectively—a **36.2×** ratio. Treat these as raw report values until units and extraction are validated.

Ibex has **60 high-fanout tags among 61 reported paths**, and **40 deep-logic tags**. Its TNS contributes approximately **94.9%** of the combined three-design TNS magnitude. This makes shared-load repair the highest-priority experiment.

The `io_constrained` tags do not establish an IO-delay root cause for these register endpoints. Long-wire delay and clock skew are also unproven without net-delay and clock-arrival decomposition. Verify that `_26153_` belongs to the relevant data-path segment before targeting it.

# 4. Regressions

**No candidate-induced endpoint regressions versus the reference were reported.** All three reference comparisons have zero regressed paths.

A separate pre/post-repair regression appears in GCD:

| Endpoint | Pre-repair slack (ns) | Post-repair slack (ns) | Δslack |
|---|---:|---:|---:|
| `dpath.a_reg.out[12]$_DFFE_PP_/D` | -0.172143 | -0.173529 | **-0.001386 ns** |

The path reports `NOR2_X2@_950_/ZN` and `INV_X1@_977_/ZN` among its slowest drivers. Shared-load changes, upstream loading from sizing, or placement changes are plausible mechanisms; the report does not distinguish them. The reference has the same result, so this regression cannot be attributed to iteration 5.

# 5. Recommendation for the next iteration

1. **Buffering/load-splitting cluster:** target Ibex’s shared high-fanout cone after confirming data-path membership. In `src/move/SplitLoadGenerator.cc` and `src/move/BufferGenerator.cc`, prioritize partitions by critical-sink slack and capacitance. Measure matched arrivals, upstream slew, WNS/TNS, area, and hold effects against the champion.

2. **Cloning cluster:** inspect `src/move/CloneGenerator.cc` for eligibility and rejection reasons around the shared driver. Test duplication that separates critical register-file sinks from other loads; include the extra upstream input capacitance in acceptance.

3. **Setup-strategy cluster:** inspect why existing buffer/clone/split moves leave this cone unresolved. Record generated, rejected, committed, and rolled-back moves by type and instance before changing move order. Test shared-load repair earlier only if those records identify an ordering barrier.

**Do not repeat feasible-runner-up sizing selection on tier A without evidence of recovered opportunities.** Any revisit must count infeasible reference winners, profitable feasible alternatives, committed replacements, and their matched endpoint timing effects. Preserve the existing `upsizeCell` API.

```json
{
  "recommended_cluster": "buffering",
  "dominant_cause": "high_fanout",
  "lesson": "Moving upstream max-capacitance feasibility into sizing selection preserved compatibility but produced zero incremental tier-A timing benefit.",
  "dead_end": "Do not repeat feasible-runner-up sizing selection without measured recovery opportunities and attributable endpoint gains.",
  "good_changes": [
    "src/move/SizeUpGenerator.cc and src/move/SizeUpGenerator.hh preserved the protected upsizeCell API; all supplied unit and smoke gates passed, but no timing benefit was measured."
  ],
  "bad_changes": [
    "src/move/SizeUpGenerator.cc moved replacementPreservesMaxCap into contender selection with zero measured WNS, TNS, or reported endpoint improvement."
  ],
  "files_to_revisit": [
    "src/move/SplitLoadGenerator.cc",
    "src/move/BufferGenerator.cc",
    "src/move/CloneGenerator.cc",
    "src/policy/SetupLegacyPolicy.cc"
  ],
  "files_to_avoid": [
    "src/move/SizeUpGenerator.cc",
    "src/move/SizeUpGenerator.hh"
  ]
}
```
