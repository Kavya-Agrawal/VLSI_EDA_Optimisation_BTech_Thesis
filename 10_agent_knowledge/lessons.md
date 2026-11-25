# Lessons

Appended by the planner after each iteration. Newest at the bottom.

## iteration 3 (sizing)

Candidate 0003 produced no timing evidence because the upsizeCell-to-upsizeCells API change broke test compilation, and all ten smoke logs failed during helper initialization.

## iteration 4 (sizing)

Absolute stage-gain ranking changed rising-edge replacement selection and failed unit gates before any benchmark timing benefit could be measured.

## iteration 5 (sizing)

Moving upstream max-capacitance feasibility into sizing selection preserved compatibility but produced zero incremental tier-A timing benefit.

## iteration 6 (buffering)

High-fanout eligibility reduced Ibex TNS by 3.52% but failed promotion because AES regressed and retained repairs on the intended drivers were not established.

## iteration 7 (buffering)

Capacitance-aware prefix selection with predicted moved-load safety regressed AES WNS by 5.341 ps and TNS by 0.984591 ns, so split retention requires measured affected-endpoint checks after legalization.

## iteration 8 (setup_strategy)

Shared-cone repair coincided with a 57.554 ns Ibex TNS gain, but uninstrumented local monotonic trials did not establish final-placement safety or runtime feasibility.

## iteration 9 (setup_strategy)

Shared-criticality ranking reduced Ibex TNS magnitude by 52.28% but changed repair trajectories enough to worsen AES and JPEG, so sharing needs bounded influence and evidence of structural concentration.

## iteration 10 (sizing)

Neighbour weighting activated on 5078 of 5086 size selections but changed only 23 choices, improving AES TNS by 0.007183 ns without WNS gain; prioritize shared-net topology repair.

## iteration 11 (buffering)

Root-only sink-violation reranking left Ibex unchanged and traded a 0.047038 ns JPEG TNS gain for a 0.150839 ns AES loss; verify activation and actual endpoint TNS before testing V-aware Pareto retention.

## iteration 12 (setup_strategy)

TNS-aware pass promotion improved Ibex TNS by 11.627 ns, but rolling checkpoint guards and stock-pass vetoes worsened WNS on every design and failed to protect AES.

## iteration 13 (setup_strategy)

A separate journaled TNS recovery phase with a fixed stock-WNS floor improved WNS on all four designs and reduced Ibex TNS by 32.39%, while still permitting individual endpoint regressions.

## iteration 14 (sizing)

Joint sizing under a fixed stock-WNS floor displaced recovery moves and improved Ibex TNS by 21.20% versus champion while surrendering 5.205 ps of Ibex WNS and 1.289 ps of JPEG WNS.

## iteration 8 (setup_strategy), measured later with a long timeout
The iteration-8 candidate (setup policy rewrite) gave the largest TNS gains seen so far: ibex TNS -65.7 -> -8.1 ns (-88%), jpeg -32.4 -> -24.4 ns (-25%), gcd also better, but aes WNS worse and repair time grew 15-115x (jpeg 36 s -> 69 min, beyond the 10-min evaluation cap). Promising direction: keep its aggressive TNS recovery but bound its effort (iteration/time budget, or only on endpoints sharing bottleneck cells) so it fits the cap and does not degrade WNS.

## iteration 15 (buffering)

Immediate-sink model-ranked SplitLoad cuts inside the stock loop regressed champion-relative score; test downstream-weighted cuts in an isolated measured phase with a monotonic WNS floor.

## iteration 16 (setup_strategy)

Multiplicative endpoint prices retained Ibex's shared-driver bias and worsened TNS magnitude by 28.53% versus champion; isolate cone diversity and structural move coverage before retuning prices.

## iteration 17 (buffering)

Zero applied trees and unchanged fanout 943 mean candidate 0017 did not test timing-driven load isolation; establish activation and measure feasible journaled variants before tuning the heuristic.

## iteration 18 (buffering)

Iteration 18 lost to champion because visit-dependent single-replica cloning did not implement the proposed atomic search, while Ibex's 943-load attributed driver belongs to the launch clock path rather than the data chain.

## iteration 19 (setup_strategy)

Measured depth-2 recovery improved JPEG baseline TNS by 0.525 ns but lost champion recovery because AES generated no trials and Ibex failed replay.
