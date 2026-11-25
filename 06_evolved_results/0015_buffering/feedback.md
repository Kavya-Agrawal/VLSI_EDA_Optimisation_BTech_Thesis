# Feedback for iteration 15 (0015_buffering, cluster buffering)

```
vs champion:
REJECT  score=-0.00064
  nangate45/gcd      WNS -0.0222 -> -0.0222 ns  TNS -0.342 -> -0.342 ns  score +0.00000
  nangate45/aes      WNS -0.0241 -> -0.0260 ns  TNS -0.999 -> -1.057 ns  score -0.00128
  nangate45/ibex     WNS -0.0742 -> -0.0740 ns  TNS -44.399 -> -44.244 ns  score +0.00007
  nangate45/jpeg     WNS -0.0853 -> -0.0880 ns  TNS -31.151 -> -30.918 ns  score -0.00134
  ! score -0.00064 below required gain +0.00200

vs baseline:
ACCEPT  score=+0.00142
  nangate45/gcd      WNS -0.0234 -> -0.0222 ns  TNS -0.475 -> -0.342 ns  score +0.00399
  nangate45/aes      WNS -0.0258 -> -0.0260 ns  TNS -1.141 -> -1.057 ns  score -0.00004
  nangate45/ibex     WNS -0.0794 -> -0.0740 ns  TNS -65.665 -> -44.244 ns  score +0.00234
  nangate45/jpeg     WNS -0.0866 -> -0.0880 ns  TNS -32.403 -> -30.918 ns  score -0.00060
```

The workspace is read-only, so I could not save `feedback.md`. Its complete content follows.

# 1. Outcome

**REJECT versus champion:** score **−0.00064**, below the required **+0.00200** gain by **0.00264**. Retain the champion.

**ACCEPT versus baseline:** score **+0.00142**. Baseline gains do not establish an improvement over the champion.

All deltas below are candidate minus comparator; positive WNS/TNS deltas mean improvement. Values use the supplied rounded metrics.

| Design | Candidate WNS (ns) | Candidate TNS (ns) | ΔWNS vs champion (ns) | ΔTNS vs champion (ns) | ΔWNS vs baseline (ns) | ΔTNS vs baseline (ns) | Score vs champion |
|---|---:|---:|---:|---:|---:|---:|---:|
| gcd | −0.0222 | −0.342 | 0.0000 | 0.000 | +0.0012 | +0.133 | +0.00000 |
| aes | −0.0260 | −1.057 | −0.0019 | −0.058 | −0.0002 | +0.084 | −0.00128 |
| ibex | −0.0740 | −44.244 | +0.0002 | +0.155 | +0.0054 | +21.421 | +0.00007 |
| jpeg | −0.0880 | −30.918 | −0.0027 | +0.233 | −0.0014 | +1.485 | −0.00134 |

AES and JPEG losses outweigh the small Ibex gain. Unit and smoke gates pass; they do not establish timing improvement. Evaluation has one replicate per design.

# 2. Did the hypothesis do what it predicted?

**The implemented candidate did not test the full stated hypothesis.** Candidate `HYPOTHESIS.md` explicitly documents deviations, and source inspection confirms them.

| Predicted mechanism | Implemented behavior |
|---|---|
| Preserve the stock loop; add a separate recovery phase and budget | Changes `SplitLoadGenerator::generate`, affecting both the stock loop and existing recovery |
| Rank drivers by violating-endpoint count × summed negative slack | Existing recovery remains unchanged; it sums negative slack along up to 400 endpoint worst paths |
| Weight each sink by downstream negative endpoint slack | Uses immediate sink slack for one transition; no downstream endpoint aggregation |
| Evaluate each cut with journaled incremental STA; commit the best | Ranks cuts with `Rdrv × (Cmoved − Cbuf)` and estimated buffer delay; no exhaustive measured comparison |
| Centroid buffer placement, clone variants, optional driver resizing | Emits buffer cuts using the lowest-drive buffer and driver location; no new combined clone/resize search |
| Enforce WNS against the last committed recovery WNS | Existing recovery compares against its initial WNS floor, which is not advanced after commits |

The change ran: cut rerankings were **0/6/23/20** for GCD/AES/Ibex/JPEG, with **0/18/61/57** emitted candidates. Existing recovery reported **17/22/30/39** commits, but these counters cover multiple move types and cannot attribute gains to the new cuts. `split_cutpoint_dropped=0` counts empty load sets; it does not mean every cut passed timing checks.

Observed effects:

- **Ibex:** TNS improves only **0.155 ns (0.35%)** versus champion; WNS improves **0.2 ps**. All ten reported worst paths still contain `AND2_X1@_26153_/ZN`, fanout **943**, with reported slew **2087753088.0**. The proposed shared-driver relief is not demonstrated.
- **JPEG:** TNS improves **0.233 ns (0.75%)**, but WNS loses **2.7 ps**. `ddin[8]/Q` remains among the worst drivers on six of the ten listed paths. A different arithmetic cone becomes worst.
- **AES:** WNS loses **1.9 ps** and TNS worsens **0.058 ns**. Seven of the ten worst paths have maximum fanout at most seven; widespread high fanout is not their primary distinguishing feature.
- **GCD:** No measurable champion-relative gain, with no emitted split candidates.

The results reject the implemented greedy-loop cut-ranking change. They do not resolve whether the separately budgeted, measured post-loop search would work. Large pre-repair improvements include stock and inherited recovery effects and must not be credited to this candidate.

# 3. Where the remaining negative slack comes from

The **five worst endpoints globally are all JPEG endpoints**. Endpoint names below are relative to `fdct_zigzag.dct_mod.`; each ends in `$_DFFE_PP_/D`.

| Rank | Endpoint | Slack (ns) | Structural evidence and likely cause | Relevant moves and likely limitation |
|---|---|---:|---|---|
| 1 | `dct_block_2.dct_unit_4.macu.mult_res[18]` | −0.088003 | 20 stages, max fanout 12; `HA_X1@_114361_/S`, `AOI21_X1@_106308_/ZN`. Deep logic plus possible weak local drive. | Size or substitute the limiting arithmetic cells, swap equivalent pins, or split their loads. A shared-trunk cut does not remove arithmetic depth; model-only selection can worsen this cone while helping others. |
| 2 | `dct_block_5.dct_unit_4.macu.mult_res[18]` | −0.085302 | 22 stages, fanout 15; `DFFR_X2@ddin[8]/Q` and `HA_X1@_114238_/S`. Shared launch loading plus deep arithmetic. | Measured launch-load isolation, legal sequential sizing, and local HA sizing. One buffer size at the driver location may add more delay than it removes; downstream endpoint benefit is not represented. |
| 3 | `dct_block_7.dct_unit_4.macu.mult_res[15]` | −0.084674 | 20 stages, fanout 15; `HA_X1@_115122_/S` has reported slew 40669004.0; `ddin[8]/Q` also appears. Deep logic with both local and shared loading. | Combine a measured trunk cut with local arithmetic sizing. Ranking by immediate sink slack cannot reliably balance these two bottlenecks. |
| 4 | `dct_block_7.dct_unit_2.macu.mult_res[18]` | −0.083894 | 22 stages, fanout 17; `FA_X1@_109354_/S`, `HA_X1@_115805_/S`. Deep arithmetic and possible weak drive. | Arithmetic cell substitution/sizing, pin swaps, or local output-load isolation. Neither named worst driver is the hypothesized launch trunk; unchanged depth limits shared-net-only repair. |
| 5 | `dct_block_5.dct_unit_4.macu.mult_res[17]` | −0.083520 | 21 stages, fanout 15; `OAI221_X1@_095447_/ZN` and `ddin[8]/Q`. Deep logic plus local slew and launch loading. | OAI sizing/pin optimization and measured launch-load partitioning. A single local-slack cut model omits downstream multiplicity and nonlinear slew effects. |

The slew numbers are retained in their reported units; their scaling needs verification before conversion to time. Worst slew alone does not establish the largest delay contribution.

These five paths support **deep logic, loading, and potentially insufficient drive**. The supplied attribution does not establish long-wire dominance, IO constraints, or clock skew for them. Design-wide IO tag counts cannot be assigned to these endpoints.

# 4. Regressions

Endpoint comparisons below use the path report’s reference, which corresponds to the baseline comparison; they are separate from champion-relative aggregate deltas.

| Design | Endpoint | Reference → candidate slack (ns) | Change |
|---|---|---:|---:|
| JPEG | `dct_block_2.dct_unit_4.macu.mult_res[18]` under `fdct_zigzag.dct_mod.` | −0.0843 → −0.0880 | −3.7 ps |
| JPEG | `dct_block_3.dct_unit_3.macu.mult_res[16]` under the same prefix | −0.0827 → −0.0828 | −0.1 ps |
| AES | `sa10_sr[3]$_DFF_P_/D` | −0.0227 → −0.0257 | −3.0 ps |
| AES | `sa33_sr[1]$_DFF_P_/D` | −0.0200 → −0.0206 | −0.6 ps |
| AES | `sa33_sr[3]$_DFF_P_/D` | −0.0258 → −0.0260 | −0.2 ps |
| Ibex | `instr_addr_o[22]` | +0.0001 → −0.0155 | −15.6 ps; newly violating |
| Ibex | `instr_addr_o[30]` | −0.0522 → −0.0587 | −6.5 ps |
| Ibex | `instr_addr_o[23]`, `[26]`, `[27]` | Respectively +0.0106 → +0.0033; +0.0267 → +0.0102; +0.0217 → +0.0155 | −7.3, −16.5, −6.2 ps |
| GCD | `resp_msg[8]` | +0.0212 → +0.0043 | −16.9 ps; remains positive |
| GCD | `resp_msg[3]`, `[2]` | +0.0255 → +0.0254; +0.0617 → +0.0610 | −0.1, −0.7 ps |

`resp_msg[9]` is marked regressed but rounds to +0.0032 ns on both sides; its magnitude cannot be recovered from those values.

**Probable mechanisms:** changing candidate order inside the stock loop changes subsequent resize, clone, and pin-swap choices. The cut model ignores wire RC, actual input slew, downstream endpoint multiplicity, and placement effects. Lowest-drive buffering can penalize moved sinks enough to create a new critical cone.

Existing global WNS/TNS admission also permits individual endpoint regressions: an output can become violating while remaining above global WNS, provided aggregate TNS improves. The fixed recovery WNS floor can surrender improvements earned earlier in recovery.

These are plausible mechanisms, not per-move causal findings. No supplied trace links a specific cut to a specific regression.

# 5. Recommendation for the next iteration

1. **Buffering — implement the isolated measured experiment.** Restore champion generator behavior. Add the post-loop phase in `src/rsz/src/policy/SetupLegacyPolicy.cc`, with independent limits. From the same checkpoint, measure each cut, legal clone alternative, and optional resize combination. Commit only the best TNS result satisfying a monotonically updated WNS floor. Log target, cut, cell, placement, measured WNS/TNS, and rejection reason.
2. **Buffering — replace immediate-sink scoring with downstream endpoint aggregation.** Deduplicate endpoints through reconvergence; rank drivers by the specified count × summed negative slack. Test capacitance-aware and spatial partitions with appropriate buffer sizes. For `_26153_/ZN`, report before/after fanout, capacitance, stage delay, slew, and affected endpoint TNS; unchanged fanout 943 would require explanation.
3. **Sizing — target JPEG arithmetic and AES local slew.** Try measured local or paired changes around JPEG `_114361_`, `_106308_`, `_115122_`, `_109354_`, `_115805_`, `_095447_`, and AES `_11702_`, `_19629_`, `_14869_`. Include equivalent arithmetic-cell substitutions where legal. Require final WNS/TNS comparison against the champion trajectory.

**Do not repeat:** model-ranked multi-cut emission inside the stock greedy loop using immediate sink slack, one lowest-drive buffer, and driver-location placement. That mechanism changed the trajectory and failed the champion comparison.

```json
{
  "recommended_cluster": "buffering",
  "dominant_cause": "deep_logic",
  "lesson": "Immediate-sink model-ranked SplitLoad cuts inside the stock loop regressed champion-relative score; test downstream-weighted cuts in an isolated measured phase with a monotonic WNS floor.",
  "dead_end": "Do not repeat greedy-loop cut reranking with a first-order RC model and one lowest-drive buffer at the driver location.",
  "good_changes": [],
  "bad_changes": [
    "src/rsz/src/move/SplitLoadGenerator.cc: rankCutPoints changes stock-loop candidate ordering and yields score -0.00064 versus champion.",
    "src/rsz/src/move/SplitLoadGenerator.cc: immediate sink slack does not implement downstream violating-endpoint weighting.",
    "src/rsz/src/move/SplitLoadGenerator.cc: lowestDriveBufferCell and driver-location placement omit buffer-size and centroid searches."
  ],
  "files_to_revisit": [
    "src/rsz/src/policy/SetupLegacyPolicy.cc",
    "src/rsz/src/move/SplitLoadGenerator.cc",
    "src/rsz/src/move/SplitLoadCandidate.cc"
  ],
  "files_to_avoid": [
    "src/rsz/src/policy/SetupParallelEvalPolicy.cc",
    "src/rsz/src/SkewBudget.hh"
  ]
}
```
