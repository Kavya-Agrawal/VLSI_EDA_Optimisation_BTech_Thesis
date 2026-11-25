# Iteration 18 — Measured best-of-k criticality-partitioned gate cloning (critical-sink replica + stock van Ginneken on tolerant sinks) for shared high-fanout drivers in the post-stock recovery phase

cluster: `buffering`

# Iteration 18 plan: timing-driven gate cloning on shared high-fanout bottlenecks, picked by measured best-of-k

## Observation

- **Where the remaining TNS is.** Ibex and JPEG carry about 98% of the remaining absolute TNS (75.6 of 76.9 ns). Ibex's ten worst paths all still cross one cell, AND2_X1 `_26153_/ZN`. That output still drives 943 loads, and the paths are 33–37 stages deep.
- **Iteration 17 never ran its idea.** It built zero trees and fanout stayed at 943. The cause is how it built candidates. A lumped-RC prefilter allowed at most four groups, each capped at 90% of one buffer's max capacitance. With 943 sinks that can't be satisfied, so nothing passed the filter. The evaluator also found that `applyFanoutTree` never resizes the original driver, there was no recovery-only gating, and the WNS floor did not ratchet.
- **Iteration 15** (model-ranked SplitLoad cut, one lowest-drive buffer) lost AES and JPEG WNS. Both buffering attempts so far insert extra stages in front of the critical sinks. On a path that is already deep, a buffer stage costs about as much delay as it saves in load.
- **What has worked.** Iteration 13 (the champion) improves all four designs because it leaves the stock loop alone and adds a journaled recovery phase afterwards. Iterations 8, 12 and 14 show that most Ibex TNS is reachable: −8.1 ns, −54.0 ns and −35.0 ns against the champion's −44.4 ns. Each of them lost WNS, either by changing the stock loop (8, 12) or by using a fixed floor that let recovery spend WNS it had already won (14).
- **Regressions to guard against.** `instr_addr_o[22]` goes from +0.0001 to −0.0155, and 13 Ibex endpoints regress. The recovery phase needs a guard on each near-zero endpoint, not only on global WNS.

## Cluster choice and why

**`buffering`**, specifically the clone and split-load decision, not the buffer-tree recipe. The last three clusters were buffering, setup_strategy, buffering, so picking buffering again is allowed (it isn't three in a row).

The evaluator's top cause is still `high_fanout` on one Ibex net that holds about 58% of total remaining TNS. That net has never actually been restructured in any iteration, because 17 never applied anything. Sizing alone can't fix a 943-load AND2_X1: iteration 10's selection changed only 23 choices, and iteration 14's DP lost WNS. Gate cloning is in the allowed move set and stock uses it only 9 times on Ibex. Cloning removes load from the critical sinks without adding a buffer stage, which avoids the problem behind iterations 15 and 17.

## Hypothesis

**Problem.** Shared high-fanout drivers on violating paths, mainly Ibex `_26153_` with 943 loads, carry critical and non-critical sinks on one net. Every critical path through them pays the delay of the full load.

**Current heuristic.**
- `CloneGenerator` splits the sinks into two spatial clusters and clones once.
- `SplitLoadGenerator` isolates the non-critical sinks behind one buffer.
- Each is ranked by a local model and tried as a single move inside the greedy loop.
- The champion's `runTnsRecovery` tries at most three stock moves per driver, so it never restructures this net.

**New approach.** Measured best-of-k criticality-partitioned cloning, run only in the post-stock recovery phase.

1. Explicitly schedule every recovery target driver with fanout of 12 or more that sits on violating paths. That covers the Ibex 943-load net and the JPEG fanout 12–17 launch drivers such as `ddin[8]/Q`.
2. Sort the sinks by required time (latest arrival minus slack per sink pin), not by position.
3. Generate k ≤ 6 variants, each applied atomically under one journal:
   - (a) A critical-only clone: the most critical q% of sinks (q from {5, 15, 30}) move to one new replica, which is then upsized with the stock size-up selection. The original driver keeps the rest.
   - (b) An m-way split into m in {2, 3, 4} replicas by required-time quantile.
   - In each variant, the slack-tolerant replica is then rebuffered with the stock `Rebuffer::rebufferNet` (van Ginneken), not a lumped model.
4. Measure every variant with incremental STA and keep the one with the best design TNS that passes all three guards:
   - a **ratcheting WNS floor**: the maximum of the stock-final WNS and the best committed recovery WNS so far;
   - a **per-endpoint guard**: any endpoint with pre-move slack above −1 ps must not fall below −1 ps;
   - **no new DRV** violations.
5. Roll back everything else.

**Why WNS/TNS should improve.**
- Critical sinks drive a load a small fraction of the size, through no extra stage. On Ibex's 33–37-stage paths this should cut tens of ps at the shared stage, across the thousands of endpoints whose paths go through it.
- Measured selection avoids the model-versus-STA disagreement that broke iterations 15 and 17.
- The ratcheting floor and endpoint guard remove the WNS loss seen in iterations 14 and 16 and the `instr_addr_o[22]` failure.

**Trigger estimate.** The stock loop is untouched; this is the rule-14 requirement.
- In recovery, at least 1 target net on Ibex and about 5–15 on JPEG and AES are evaluated with k variants each. That is roughly 30–90 measured trials, and I expect about 5–15 committed structural moves per design.
- Against the recovery-phase moves (17/22/30/34), that changes 15–50% of decisions.
- Against stock move totals (AES 2,078; Ibex 172) it is under 5%. However, the Ibex net lies on all ten worst paths and, by the evaluator's attribution, on the bulk of Ibex's −44 ns TNS. So the count of affected endpoints is in the thousands even though the number of moves is small.
- I'm stating this shortfall openly rather than inflating the trigger count.

**Risks.**
- Clone placement and legalization collateral (the iteration 7 lesson). Mitigation: place each replica at the centroid of its sink group and accept only after the evaluator's post-legalization check.
- Extra input load on the AND2 fan-in cone. Mitigation: it is measured in incremental STA.
- Runtime from k incremental STA updates on a 943-sink net. Mitigation: k ≤ 6, a cap of 40 targets, and a per-phase time print.

## Implementation sketch

- **`src/move/CloneGenerator.cc` and `.hh`.** Add `generateCriticalityPartitions(driver, k)`. It returns variant descriptors (sink sets ordered by required time, replica count, upsize flag). The stock `generate()` path stays byte-identical outside recovery and is gated by a recovery-mode flag.
- **`src/move/CloneCandidate.cc` and `.hh`.** Add `applyPartition()`. It creates the replicas, reconnects the sink sets, places each replica at the centroid of its sinks, and upsizes the critical replica (reusing the size-up master selection). It then optionally calls the stock `Rebuffer::rebufferNet` on the tolerant net, all inside one journal.
- **`src/policy/SetupLegacyPolicy.cc::runTnsRecovery`.**
  - Explicitly schedule drivers with fanout of 12 or more from the bottleneck ranking. Run the k variants, each as a journal, then incremental STA, then measurement, then rollback, and re-apply only the best variant.
  - Replace the one-time WNS floor capture with a ratcheting floor.
  - Snapshot the endpoints with slack above −1 ps before each trial, and veto any trial that pushes one of them below −1 ps.
- **Counters (`RSZ_EVOLVE`), printed per design:**
  - targets visited, eligible, and variants generated;
  - variants rejected, split by WNS floor, endpoint guard, DRV, and no TNS gain;
  - committed moves, with fanout before and after per committed net;
  - predicted vs. measured dTNS;
  - stock-phase move counts, to prove the stock phase is unchanged;
  - floor value per round and recovery runtime.

## Success criteria

- **Activation:** the Ibex `_26153_` net is restructured, with fanout on the critical replica at or below 100 in the path report and at least one committed clone partition on Ibex and JPEG.
- **Stock phase unchanged:** stock-phase move counts are identical to the champion's.
- **Ibex:** TNS better than −40 ns (at least 10% over the champion's −44.4 ns), with WNS at least as good as −0.0742.
- **AES, gcd, JPEG:** WNS no worse than the champion's; JPEG TNS better than −31.15 ns.
- **Endpoint guard:** `instr_addr_o[22]` slack ≥ −1 ps.
- **Overall:** score vs. champion ≥ +0.002, and JPEG finishes within the timeout.

## Fallback if it fails

- **Variants are generated but rejected by the floor or guard:** use the rejection-reason counters to decide between relaxing to a per-endpoint TNS budget and moving to `sizing` coordinated launch/HA/FA bundles for JPEG.
- **Committed but no gain:** treat high-fanout restructuring of Ibex as falsified. Rotate to `timing_model` (slew-propagated delay estimates for recovery ranking) or `sizing`. Do not try another buffering variant.

```json
{"cluster": "buffering", "title": "Measured best-of-k criticality-partitioned gate cloning (critical-sink replica + stock van Ginneken on tolerant sinks) for shared high-fanout drivers in the post-stock recovery phase", "hypothesis": "Shared high-fanout drivers on violating paths (Ibex AND2_X1 _26153_ with 943 loads on all ten worst paths; JPEG fanout 12-17 launch drivers) make every critical path pay the full net load, and the stock spatial 2-way clone or single-buffer split never restructures them; iteration 17's lumped-RC tree prefilter applied zero trees. Instead, in runTnsRecovery only, explicitly schedule drivers with fanout >=12, sort sinks by required time, and generate up to 6 atomic variants: a critical-only upsized replica (top 5/15/30% of sinks) or an m-way required-time-quantile clone split (m=2..4), with the tolerant net rebuffered by the stock Rebuffer::rebufferNet. Every variant is evaluated by journaled incremental STA and the best design-TNS variant is kept only if it satisfies a ratcheting WNS floor, a per-endpoint guard (pre-move slack > -1 ps must stay > -1 ps) and no new DRV. Cloning removes load from critical sinks without adding a buffer stage, so deep (33-37 stage) Ibex paths gain tens of ps at the shared stage across thousands of endpoints while measured selection avoids the model/STA mismatch of iterations 15 and 17.", "files": ["src/move/CloneGenerator.cc", "src/move/CloneGenerator.hh", "src/move/CloneCandidate.cc", "src/move/CloneCandidate.hh", "src/policy/SetupLegacyPolicy.cc", "src/policy/SetupLegacyPolicy.hh"], "evidence_iterations": [13, 8, 14, 15, 17], "success_criteria": "Ibex _26153_ critical-replica fanout <=100 with >=1 committed partition on Ibex and JPEG, stock-phase move counts identical, Ibex TNS better than -40 ns, no design WNS worse than champion, instr_addr_o[22] >= -1 ps, score vs champion >= +0.002", "risk": "Clone placement/legalization collateral and extra fan-in load on the AND2 cone, plus runtime from k incremental STA trials on a 943-sink net (capped at k<=6, 40 targets).", "rule_updates": "A structural-move hypothesis is untested unless RSZ_EVOLVE counters show at least one committed application on the named target net; zero-application runs must be logged as infrastructure, not as evidence against the idea."}
```
