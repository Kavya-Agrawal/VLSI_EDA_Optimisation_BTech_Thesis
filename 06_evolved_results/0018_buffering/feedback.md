# Feedback for iteration 18 (0018_buffering, cluster buffering)

```
vs champion:
REJECT  score=-0.00024
  nangate45/gcd      WNS -0.0222 -> -0.0222 ns  TNS -0.342 -> -0.342 ns  score +0.00000
  nangate45/aes      WNS -0.0241 -> -0.0242 ns  TNS -0.999 -> -1.179 ns  score -0.00013
  nangate45/ibex     WNS -0.0742 -> -0.0773 ns  TNS -44.399 -> -45.290 ns  score -0.00080
  nangate45/jpeg     WNS -0.0853 -> -0.0853 ns  TNS -31.151 -> -31.242 ns  score -0.00001
  ! score -0.00024 below required gain +0.00200

vs baseline:
ACCEPT  score=+0.00182
  nangate45/gcd      WNS -0.0234 -> -0.0222 ns  TNS -0.475 -> -0.342 ns  score +0.00399
  nangate45/aes      WNS -0.0258 -> -0.0242 ns  TNS -1.141 -> -1.179 ns  score +0.00110
  nangate45/ibex     WNS -0.0794 -> -0.0773 ns  TNS -65.665 -> -45.290 ns  score +0.00147
  nangate45/jpeg     WNS -0.0866 -> -0.0853 ns  TNS -32.403 -> -31.242 ns  score +0.00073
```

Cannot save `feedback.md`: this workspace permits read-only access. Completed content follows.

# 1. Outcome

**REJECT against champion:** score **−0.00024**, versus required **+0.00200**; shortfall **0.00224**. Baseline comparison accepts at **+0.00182**, but does not justify replacing the champion.

Deltas below are candidate minus reference; positive means improved. WNS deltas use the unrounded local verdict data.

| Design | Final WNS (ns) | Final TNS (ns) | ΔWNS vs champion (ps) | ΔTNS vs champion (ns) | ΔWNS vs baseline (ps) | ΔTNS vs baseline (ns) |
|---|---:|---:|---:|---:|---:|---:|
| gcd | −0.022215 | −0.342014 | 0.000 | 0.000000 | +1.151 | +0.132796 |
| aes | −0.024182 | −1.179469 | −0.054 | −0.180651 | +1.659 | −0.038511 |
| ibex | −0.077259 | −45.290379 | −3.019 | −0.891021 | +2.153 | +20.375069 |
| jpeg | −0.085302 | −31.242 | 0.000 | −0.091433 | +1.321 | +1.161109 |

Ibex accounts for approximately **85% of the summed per-design score loss** against champion. AES negative-slack magnitude increases **18.09%** against champion; Ibex increases **2.01%**.

All six unit-test targets and ten smoke tests passed. Functional gates do not establish timing benefit.

# 2. Did the hypothesis do what it predicted?

**The implemented candidate did not exercise the proposed algorithm completely, and the predicted timing effect did not appear.**

Source inspection of `src/rsz/src/move/CloneGenerator.cc` and `src/rsz/src/policy/SetupLegacyPolicy.cc` finds:

| Proposed mechanism | Implemented behavior |
|---|---|
| Explicit recovery scheduling of fanout ≥12 drivers | Existing ranking by slack-weighted violating-path coverage; fanout threshold only inside clone generation |
| Six alternatives evaluated from one starting state | One candidate per generator call; repeated visits rotate variants after an initial stock candidate |
| Upsized critical replica | Variant replica uses `original_cell`, preserving strength |
| Atomic 2–4-way quantile splits | Six single-replica fractions: 5%, 15%, 30%, 50%, 33%, 25% |
| Required-time ordering | Sink slack relative to driver slack |
| Rebuffer tolerant remainder | No such operation in `CloneCandidate::applyClone()` |
| Best design-TNS variant selected | First qualifying repair is committed |
| Ratcheting WNS floor | Recovery-entry floor remains fixed |
| Endpoint guard at −1 ps | No explicit endpoint guard in the recovery acceptance loop |

The variant state belongs to the shared clone generator; it is not explicitly restricted to `runTnsRecovery`.

Counters establish candidate generation, **not committed topology changes**:

| Design | Variant generations | Drivers reaching variants | Summed proposed moved loads |
|---|---:|---:|---:|
| gcd | 0 | 0 | 0 |
| aes | 7 | 3 | 20 |
| ibex | 25 | 5 | 146 |
| jpeg | 15 | 9 | 89 |

These counters increment before candidate acceptance and can include rejected proposals and repeated sinks.

**Ibex:** all ten worst attributed paths retain `_26153_/ZN`, fanout **943**, and **36 reported stages**. Endpoint `[703]` improves only **2.153 ps versus baseline**, while losing **3.019 ps versus champion**. There is no evidence of the predicted tens-of-ps shared-stage gain.

There is also a targeting error in the original hypothesis: `paths_post.json` places `_26153_/ZN` immediately before the launch flop’s **CK** pin. It is a **clock-path driver**, not a shared combinational data stage. The textual STA report uses ideal clock latency and starts data propagation at the launch flop. Its enormous attributed slew therefore does not establish that every data path pays that net’s delay. Clock-aware analysis is required before attempting to restructure it.

**JPEG:** launch drivers remain sequential `DFFR_X2` cells, which the clone generator’s single-output-combinational eligibility check excludes. Final repair statistics report no clones or inserted buffers, despite 15 generated variants. WNS is unchanged against champion; TNS worsens **0.091433 ns**.

**GCD:** zero variants and identical champion timing. **AES:** generated variants coexist with worse WNS and TNS; generation alone supplies no evidence of benefit.

# 3. Where the remaining negative slack comes from

The five globally worst supplied endpoints are all JPEG endpoints. Prefix below is `fdct_zigzag.dct_mod.`.

| Endpoint | Slack (ps) | Likely cause | Relevant moves and likely limitation |
|---|---:|---|---|
| `dct_block_5.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | −85.302 | Deep logic: 22 stages; launch fanout 15; weak `HA_X1@_114238_` | Size or split launch loads; resize HA. Sequential launch driver is ineligible for cloning; no committed buffering is reported. |
| `dct_block_7.dct_unit_4.macu.mult_res[15]$_DFFE_PP_/D` | −84.674 | Deep logic: 20 stages; fanout 15; `HA_X1@_115122_` has worst reported slew | HA sizing/pin optimization and launch-load isolation. Critical-fraction combinational cloning does not directly address launch-Q loading or serial arithmetic delay. |
| `dct_block_7.dct_unit_2.macu.mult_res[18]$_DFFE_PP_/D` | −83.894 | Deep logic: 22 stages; fanout 17; `FA_X1@_109354_`, `HA_X1@_115805_` | Joint arithmetic-cell sizing and legal pin swaps. Single-driver trials may reject moves whose input-capacitance penalty requires coordinated upstream resizing. |
| `dct_block_5.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D` | −83.520 | Deep logic: 21 stages; fanout 15; weak `OAI221_X1@_095447_` | OAI sizing plus launch-load split. Added replicas can increase upstream load; current variants do not include compensating sizing. |
| `dct_block_1.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D` | −83.002 | Deep logic: 23 stages; fanout 17; `HA_X1@_115070_`, `AOI21_X1@_081689_` | Joint HA/AOI sizing or arithmetic restructuring. Load partitioning alone cannot remove serial logic depth. |

Deep logic and weak arithmetic drivers are supported by these paths. Long-wire dominance, IO-constraint dominance, and clock-skew dominance are not established for these five endpoints. Preserve reported slew values as diagnostic rankings until their exported units are verified.

# 4. Regressions

Endpoint comparisons below use the supplied path-report reference, which is distinct from the champion comparison.

| Design / endpoint | Slack change (ps) | Probable mechanism |
|---|---:|---|
| Ibex `instr_addr_o[22]` | +0.1 → −16.2: **−16.3** | Shared-cone loading or changed repair sequence; creates a violation from a previously positive endpoint |
| Ibex `instr_addr_o[23]` | +10.6 → +3.0: **−7.6** | Shared-cone delay increase |
| Ibex `instr_addr_o[26]` | +26.7 → +9.8: **−16.9** | Shared-cone loading or sizing tradeoff |
| Ibex `instr_addr_o[27]` | +21.7 → +15.2: **−6.5** | Same likely collateral mechanism |
| Ibex `instr_addr_o[24]` | +30.5 → +21.6: **−8.9** | Same likely collateral mechanism |
| AES `sa02_sr[7]$_DFF_P_/D` | −21.1 → −22.2: **≈−1.1** | Already-violating endpoint can deteriorate while aggregate TNS improves |
| GCD `resp_msg[8]` | +21.2 → +4.3: **−16.9** | Output-path collateral delay; remains positive |
| JPEG block 3/unit 3/result `[16]` | −82.7 → −82.8: **≈−0.1** | Small local sizing or loading tradeoff |
| JPEG block 2/unit 2/result `[16]` | −82.5 → −82.6: **≈−0.1** | Same |

GCD also loses approximately **0.1 ps** at `resp_msg[3]` and **0.7 ps** at `resp_msg[2]`; the reported `resp_msg[9]` regression is below displayed precision.

The Ibex `[22]` transition violates the intended −1 ps endpoint protection at the full-run level. The present recovery loop lacks that explicit guard; the supplied results do not identify which phase caused the crossing.

A plausible source of collateral delay is replica input capacitance: `CloneCandidate::connectCloneInputs()` attaches each replica to the original input nets. No per-move trace proves that cloning caused these particular endpoint regressions.

# 5. Recommendation for the next iteration

**Recommended cluster: `setup_strategy`.** Rank options as follows:

1. **Target actual data-arc delay.** Separate clock-path attribution from data-path ranking. On Ibex, the textual `[703]` path contains six consecutive `FA_X1` arcs totaling approximately **679 ps**, followed by an HA arc of **48 ps**. Trial coordinated sizing and legal pin swaps across this chain and its upstream drivers, using journaled STA to measure net benefit.

2. **Implement the intended acceptance contract.** In `SetupLegacyPolicy.cc`, ratchet the WNS floor after each commit, snapshot every endpoint above −1 ps, reject crossings below −1 ps, and compare alternatives from the same restored design state. Record per-variant WNS, TNS, endpoint and DRV rejection reasons. Recheck timing after subsequent repair phases.

3. **Use launch-load splitting for JPEG.** Trial buffering tolerant sinks of `ddin[8]/Q` and similarly loaded sequential outputs while preserving direct critical connections. Measure whether launch delay reduction outweighs added buffer delay; do not route these targets through combinational cloning.

4. **If retaining clone experiments, complete atomic variants.** Isolate them to recovery, jointly evaluate replica sizing and tolerant-net rebuffering, and implement actual multiway partitions. Count generated, applied, rejected and committed variants separately.

**Do not repeat:** six visit-dependent, same-strength single-replica fractions presented as an atomic quantile-split experiment. They failed to improve any design against champion and did not test the proposed restructuring.

```json
{
  "recommended_cluster": "setup_strategy",
  "dominant_cause": "deep_logic",
  "lesson": "Iteration 18 lost to champion because visit-dependent single-replica cloning did not implement the proposed atomic search, while Ibex's 943-load attributed driver belongs to the launch clock path rather than the data chain.",
  "dead_end": "Do not repeat same-strength critical-fraction clone rotation without isolated atomic evaluation and verified data-path targeting.",
  "good_changes": [
    "src/rsz/src/policy/SetupLegacyPolicy.cc: journaled STA evaluates measured WNS and TNS, but its benefit is inherited and does not establish a gain from iteration 18",
    "src/rsz/src/move/CloneGenerator.cc: counters establish variant generation, though they do not measure committed moves"
  ],
  "bad_changes": [
    "src/rsz/src/move/CloneGenerator.cc: shared visit-dependent state changes clone proposals outside an explicit recovery-only search",
    "src/rsz/src/move/CloneGenerator.cc: same-strength single-replica fractions omit upsizing, multiway splitting and tolerant-net rebuffering",
    "src/rsz/src/policy/SetupLegacyPolicy.cc: fixed WNS floor and aggregate-TNS acceptance omit the proposed endpoint guard and best-variant comparison"
  ],
  "files_to_revisit": [
    "src/rsz/src/policy/SetupLegacyPolicy.cc",
    "src/rsz/src/move/CloneGenerator.cc",
    "src/rsz/src/move/CloneGenerator.hh",
    "src/rsz/src/move/CloneCandidate.cc",
    "src/rsz/src/Rebuffer.cc"
  ],
  "files_to_avoid": [
    "src/rsz/src/SkewBudget.cc",
    "src/rsz/src/RepairDesign.cc"
  ]
}
```
