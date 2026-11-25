# Iteration 13 — Two-phase repair: unchanged stock LEGACY loop, then a bottleneck-driven TNS-recovery phase with a hard post-stock WNS floor

cluster: `setup_strategy`

# Iteration 13 plan: a TNS phase after stock repair that never gives back WNS

## Observation

- **Changes that help Ibex also break AES.** Three valid experiments that aimed at shared cones or TNS each cut Ibex TNS by a lot:
  - iter 8: +57.6 ns TNS and +18.9 ps WNS, but JPEG timed out.
  - iter 9: +34.3 ns TNS.
  - iter 12: +11.6 ns TNS.
- **In every one of those, AES got worse, and the cause was the same.** Each change was put inside the stock LEGACY repair loop, so it changed that loop's path through the search:
  - iter 8: AES WNS −16.8 ps.
  - iter 9: AES WNS −14.6 ps, and JPEG's resizes fell from 282 to 54.
  - iter 12: WNS got worse on all four designs, and AES alone accounts for about 65% of the score loss.
- **Stock already stops in a good place on AES and gcd.** Stock gets AES WNS from −79 to −26 ps, and the AES endpoint `sa23_sr[0]` reaches about −24 ps under stock. None of our in-loop changes has kept that result.
- **The leftover violations sit in a few shared trunks.**
  - Ibex: the `_26153_` trunk (fanout 943) is on all 10 of the worst Ibex paths, and stock leaves 65.7 ns of TNS.
  - JPEG: the five worst endpoints share drivers such as `HA_X1@_113899_` and the `ddin[8]` launch driver, and stock leaves 32.4 ns of TNS.
- **Takeaway.** The signal that shared-bottleneck repair is worth doing is real. Where it goes in the flow is what has been going wrong.

## Cluster choice and why

**`setup_strategy`.** This is the second time in a row, which the rotation rule allows.

This is not a retreat from iter 12. Iter 12 changed the acceptance rule inside the loop, and the evaluator's options 1 and 2 would only re-tune that rule, which counts as a narrower variant. This plan changes how the search is ordered instead:

- The repair is split into two phases, each with its own objective (lexicographic phase ordering), instead of one greedy loop with a blended acceptance rule.
- The second phase picks targets by how many violating paths a driver sits on (shared bottlenecks), not by walking endpoints one at a time.
- The stock loop is not touched at all.

## Hypothesis

- **Problem:** Stock LEGACY repair is greedy and works on the worst path first, one endpoint at a time. Once WNS stops improving it stops, leaving large TNS on shared trunks:
  - Ibex: −65.7 ns
  - JPEG: −32.4 ns
- **What happens today:** `SetupLegacyPolicy` picks paths in endpoint order and moves on by endpoint slack and design WNS (`pathImproved` / `passAccepted`). Any later policies (the last-gasp and TNS policies) still work per endpoint.
- **What changes:** stock repair runs exactly as it does now. Then a new **bottleneck TNS phase** runs:
  1. **Record a floor.** Take a snapshot of the design WNS after stock repair (W\*) and fix it as a hard floor.
  2. **Find shared bottlenecks.** Collect up to N violating paths (N=400), in rank order. For each driver pin, compute a score: the sum of (negative slack) over the violating paths that pass through it. That makes it a multi-endpoint sharing count weighted by slack.
  3. **Try the stock moves on the top drivers.** For the top K drivers (K=20 per round), try the stock move generators in their usual order (size-up, swap-pins, buffer, clone, split-load) inside a journal.
  4. **Keep or undo each move.** After an incremental timing update, keep a move only if both hold:
     - design WNS is still at or above the floor W\* (the floor is fixed at W\*; it is not reset after each pass, unlike iter 12's rolling 1 ps guard);
     - the measured design TNS improves by at least ε (0.5 ps).
     Otherwise undo it.
  5. **Repeat or stop.** Rebuild the bottleneck scores and do another round. Stop after R=5 rounds, or after a round where nothing was kept, or when a move cap is reached (10% of the stock move count, at least 30 moves).
- **Why WNS/TNS should improve:**
  - The stock trajectory and final state are reproduced exactly, so no design can end below stock WNS. That removes the AES/gcd failure seen in iterations 8, 9 and 12.
  - TNS can only go down, because every kept move improves measured TNS.
  - Trunk and shared-driver moves (on the `_26153_` branches and the JPEG HA/FA drivers) repair many endpoints at once. That is the mechanism behind iter 8's +57 ns and iter 9's +34 ns on Ibex, here without the side effects.
  - A move on a shared driver of the worst cone can also raise WNS above W\*.
- **Risks:**
  1. The score may weight WNS so heavily that gains in TNS alone fall short of +0.002. In iter 12, +11.6 ns of Ibex TNS was worth only about +0.0006 before the WNS penalty.
  2. Run time on JPEG. Iter 8 timed out at 1800 s, so this needs the move and round caps plus a wall-time check expressed as a count of evaluations.
  3. Gains measured before detailed placement may disappear after legalization.
  4. Recomputing the full TNS after every trial costs time; incremental STA should keep this manageable.

## Trigger estimate

The stock decisions change in **0%** of cases by construction. The new phase only adds moves:

| Design | Stock moves | Phase cap (10% of stock, min 30) | Trials expected |
|---|---:|---:|---|
| ibex | 172 | about 30 kept moves (about 17% on top of stock) | ≥ 100 |
| aes | about 2,078 | about 200 kept moves (≥ 5% on top of stock) | — |
| jpeg | about 399 | about 40 kept moves | — |

## Implementation sketch

- **`src/policy/SetupLegacyPolicy.cc` / `.hh`:** leave the stock loop unchanged. Add `runBottleneckTnsPhase()`, called once after the stock repair finishes and before the final checkpoint is returned. It uses the existing journal / checkpoint begin, restore and commit through `MoveCommitter`.
- **`src/policy/BottleneckAnalysis.cc` / `.hh`:** add the driver scoring, i.e. the sum of slack over the top-N violating paths, with each path enumerated through `PathExpanded`. Ties break deterministically by pin name (no ordering keyed on pointers).
- **`src/Optimizer.cc`:** add the phase toggle, on by default, and print the counters.
- **Required `RSZ_EVOLVE` counters** (to satisfy the iter 9 and iter 12 rules):
  - `bneck_rounds`, `trials`, `kept`, `rejected_wns_floor`, `rejected_no_tns_gain`
  - summed predicted dTNS of kept moves
  - W\* and the final WNS
  - phase runtime
  - the number of kept moves per generator type

## Success criteria

- **WNS:** no design ends with worse WNS than the champion (Δ ≥ 0 on gcd, aes, ibex and jpeg).
- **TNS:**
  - Ibex: improves by ≥ 10 ns.
  - JPEG: improves by ≥ 1 ns.
  - AES: improves by ≥ 0.05 ns.
- **Score:** aggregate ≥ +0.002.
- **Counters:** `kept` > 0 on every design except possibly gcd.
- **Runtime:** JPEG finishes within the timeout.
- **Path report:** fewer of Ibex's top-10 worst paths go through `_26153_`.

## Fallback if it fails

- **Moves are kept but the score is still below +0.002:** the scoring is WNS-dominated. Point the same phase at the cone of the single worst endpoint, keeping the hard floor and also requiring a WNS gain.
- **Few moves are kept:** the stock generators cannot produce the structural fix needed. Switch to `buffering` and build bounded trunk / split-load candidates for the top-scored drivers (the evaluator's option 3).
- **Gains vanish after legalization:** add a re-check after detailed placement.

```json
{"cluster": "setup_strategy", "title": "Two-phase repair: unchanged stock LEGACY loop, then a bottleneck-driven TNS-recovery phase with a hard post-stock WNS floor", "hypothesis": "Every in-loop change so far (iters 8, 9, 12) found large Ibex TNS gains from shared-cone/TNS-aware repair but perturbed the stock trajectory and lost WNS on AES/gcd/JPEG. Instead of modifying the greedy worst-path-first loop, run it unchanged, snapshot design WNS W*, then run a separate phase that ranks driver pins by the slack-weighted count of violating paths through them (top-N=400 paths) and trials stock generator moves on the top-K drivers under a journal, keeping a move only if design WNS >= W* (absolute, non-rolling) and measured design TNS improves by >= 0.5 ps. Rounds repeat with re-ranking until no move is kept, 5 rounds pass, or a move cap of max(30, 10% of stock moves) is hit. This makes final WNS >= stock by construction while harvesting shared-trunk TNS (e.g. the Ibex _26153_ fanout-943 trunk, the JPEG HA/FA drivers), and moves on shared drivers of the worst cone can also raise WNS.", "files": ["src/policy/SetupLegacyPolicy.cc", "src/policy/SetupLegacyPolicy.hh", "src/policy/BottleneckAnalysis.cc", "src/policy/BottleneckAnalysis.hh", "src/Optimizer.cc"], "evidence_iterations": [8, 9, 12], "success_criteria": "No design WNS worse than champion; Ibex TNS +10 ns or more, JPEG +1 ns or more, AES TNS not worse; aggregate score >= +0.002; RSZ_EVOLVE kept>0 and JPEG within timeout.", "risk": "TNS-only gains may be under-weighted by the score, and per-trial TNS refresh may slow JPEG; caps on moves and rounds bound the runtime.", "rule_updates": "Once in-loop changes have perturbed stock trajectories in two or more iterations, prefer post-stock phases with an absolute (non-rolling) WNS floor anchored to the stock final state, and print the floor value and per-phase kept/rejected counts."}
```
