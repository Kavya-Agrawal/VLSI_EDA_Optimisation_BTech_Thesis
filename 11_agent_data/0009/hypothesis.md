# Iteration 9 — Rank repair targets by slack-weighted count of violating endpoints sharing each driver (multi-endpoint path-sharing) instead of per-path load delay

cluster: `setup_strategy`

Codebase grounding is done (I found the stock driver ranking in `SetupLegacyBase::rankPathDrivers` / `repairPath`). Here is the plan for iteration 9.

# Iteration 9 plan: rank repair targets by how many violating endpoints share them

## Observation
- **Iteration 8** (measured selection in `setup_strategy`) did not pass. Its score was +0.00063 and JPEG timed out. Even so, Ibex TNS went from -65.7 to -8.1 ns, and the worst Ibex endpoints all share one 42-stage cone through `AND2_X1@_26153_/ZN`, which drives a fanout of 943. Most of the remaining Ibex TNS comes from a few drivers that sit on many violating paths. Stock rsz never sees this, because it repairs one endpoint's worst path at a time.
- **Iteration 6** points the same way: allowing shared high-fanout drivers to be rebuffered cut Ibex TNS by 14.6 ns. It failed because the AES fix was a *buffering* change that regressed AES.
- **What hurt AES in iteration 8** was the acceptance and search machinery, not the target choice. That machinery was strict per-move admission with one winner per pass. It collapsed the move mix (612 resizes instead of 1388, 2 pin swaps instead of 132) and caused the timeout.
- **The stock driver ranking is local.** `SetupLegacyBase::rankPathDrivers` (`SetupLegacyBase.cc:414`) sorts the drivers on one endpoint's worst path by load-dependent arc delay only. `repairPath` (`:814`) then works down that list until `repairBudget` runs out. A driver on 300 violating paths ranks the same as a driver on 1 if their load delay is equal.

## Cluster choice and why
**`setup_strategy`**: this is its second iteration in a row, which the rotation rule allows. It is a different paradigm from iteration 8:
- Iteration 8 changed *acceptance*: trial each move, measure it, admit one winner.
- This plan changes *target ranking*: multi-endpoint path sharing, where the cell on the most violating paths gets fixed first.

Acceptance, generators, the pass budget and the move mix all stay stock. That keeps the AES sequences that iteration 8 suppressed, and adds no trial cost, so JPEG should not time out. The dominant cause is a high-fanout shared driver plus deep logic. That is a ranking problem, so it belongs in this cluster rather than in buffering, where iterations 6 and 7 already failed.

## Hypothesis
- **Problem:** Each per-endpoint pass spends its repair budget on the driver with the largest local load delay on *that* endpoint's path. Drivers shared by hundreds of violating endpoints get no extra priority. They are repaired late, or partly and repeatedly, and TNS stays high.
- **Current heuristic:** Rank by `load_delay = arcDelay − intrinsicDelay` per stage. It is greedy and looks only at one endpoint, with worst-endpoint-first order.
- **New approach (endpoint-sharing criticality):**
  1. At the start of each main-loop round in `runMainRepairLoop`, build a `SharedCriticality` map. Take the top N violating endpoints by slack (N = min(#violators, 400), a deterministic cap). For each one, expand its worst path once and add `w_e = −slack_e / |WNS|` to every driver pin on that path. This gives the slack-weighted count of violating paths through each driver.
  2. In `rankPathDrivers`, rank each driver by `score = load_delay × (1 + α · share(pin))`, with α = 1 normalised so that the top-shared driver can outrank a driver with up to 3–5× its load delay.
  3. Refresh the map every K = 25 endpoint repairs, or when TNS has improved by more than 5% since the last build. The map is keyed by vertex id in a `std::vector`, so results stay deterministic.
- **Why WNS/TNS should improve:** A move on a driver with share s improves s endpoints at once, so TNS gain per move rises roughly with s. On Ibex the `_26153_` cone should be attacked on the first passes of every regfile endpoint, not only when it happens to have the largest local load delay. It then gets resized, cloned or buffered by the stock generators early. WNS follows because the worst endpoints are exactly these shared ones. On AES the sharing is spread out (fanout ≤ 18, many sbox cones), so the ranking stays close to stock and the move mix is unchanged. That avoids iteration 8's AES regression.
- **Risks:**
  - Over-focus on one shared driver whose generators cannot legally improve it. Mitigation: the stock "no change, so move on to the next target" fall-through still applies.
  - Collateral damage on non-violating sinks of a heavily loaded net, like gcd `resp_msg[8]` in iteration 8. Acceptance is unchanged and still uses the stock WNS/TNS check.
  - Map build cost: at most 400 path expansions per refresh. That is small next to repair, but it will be timed.

## Implementation sketch
- `src/policy/SetupLegacyBase.hh/.cc`:
  - Add the `SharedCriticality` member: a vector of float indexed by vertex id, plus a build epoch.
  - Add `buildSharedCriticality(const ViolatingEnds&)`.
  - Change `rankPathDrivers` to multiply by `(1 + α·share)` and keep the existing tie-break so ordering stays deterministic.
  - Leave the `repairPath` structure untouched.
- `src/policy/SetupLegacyPolicy.cc`: call the build in `runMainRepairLoop` (`:386`) before the endpoint loop, and refresh it in `repairEndpoint` every K endpoints.
- **Instrumentation (required):** print `RSZ_EVOLVE shared_rank builds=… endpoints_scanned=… top_share=… rank_changed_first=… rank_changed_any=… build_ms=…`. Here `rank_changed_first` counts passes where the top target differs from the stock order. The counters are computed by sorting both ways.
- Do not touch the generators, `MoveCommitter`, or acceptance (`pathImproved`).

## Trigger estimate
Ranking changes the first target on any pass where the path contains a driver with share > 0.3, which describes nearly all passes on shared cones.
- **Ibex** (149 resizes, 9 clones): the first-target order is expected to change on ≥ 40% of passes, about 60+ decisions.
- **AES** (1388 resizes, 481 buffers, 132 swaps, 70 clones): about 15–25% of passes, so 300+ decisions. That is above the 5% bar.
- `rank_changed_first / passes` will be checked against these figures.

## Success criteria
- **Ibex:** TNS better than −40 ns (stock −65.7), WNS ≥ −0.070 ns. The `_26153_/ZN` driver is resized or cloned, with clones above the stock 9.
- **AES:** WNS ≥ −0.0258 (no regression), and the resize/swap mix stays within ±30% of stock.
- **JPEG:** finishes under 1800 s, with TNS ≥ −32.4.
- **Overall:** score ≥ +0.002, with `RSZ_EVOLVE shared_rank` lines present in all four logs.

## Fallback if it fails
- **If Ibex improves but AES regresses:** limit the sharing weight to drivers whose share exceeds a fanout-normalised threshold. That turns this into shared-cone bundling. Then move to `buffering` with an atomic clone/partition for the top-share driver only, using iteration 8's recommendation 3.
- **If there are no ranking changes:** the hypothesis is falsified for this flow. Move to `sizing` with Lagrangian-relaxation sensitivity using the existing `LRSubproblem.cc`.

```json
{"cluster": "setup_strategy",
 "title": "Rank repair targets by slack-weighted count of violating endpoints sharing each driver (multi-endpoint path-sharing) instead of per-path load delay",
 "hypothesis": "Stock SetupLegacyBase::rankPathDrivers orders drivers on a single endpoint's worst path by local load-dependent delay, so a driver on hundreds of violating paths (Ibex _26153_/ZN, fanout 943) gets no priority over a driver on one path. Build a deterministic, capped (top 400 violators, refreshed every 25 endpoints) shared-criticality map summing normalised negative slack of every violating endpoint whose worst path passes through each driver, and rank targets by load_delay*(1+share). Acceptance, generators and repair budget stay stock, avoiding iteration 8's admission/trial machinery that collapsed AES's move mix and timed out JPEG. Each move on a high-share driver improves many endpoints at once, so TNS should drop sharply on Ibex/JPEG while AES (diffuse sharing) stays near stock. RSZ_EVOLVE counters will report builds, rank changes and build time.",
 "files": ["src/policy/SetupLegacyBase.cc", "src/policy/SetupLegacyBase.hh", "src/policy/SetupLegacyPolicy.cc", "src/policy/SetupLegacyPolicy.hh"],
 "evidence_iterations": [8, 6, 7],
 "success_criteria": "Ibex TNS > -40 ns and WNS >= -0.070; AES WNS >= -0.0258; JPEG completes <1800 s with TNS >= -32.4; score >= +0.002; RSZ_EVOLVE shared_rank lines in all logs with rank_changed_first >= 5% of passes on aes and ibex",
 "risk": "Over-focusing on a shared driver whose generators cannot improve it, or collateral slack loss on non-violating sinks of reloaded nets (gcd resp_msg[8]-style).",
 "rule_updates": "Every candidate must print RSZ_EVOLVE counters showing how often the new decision differed from stock; candidates adding per-move trials must report per-phase runtime and finish JPEG within the timeout."}
```
