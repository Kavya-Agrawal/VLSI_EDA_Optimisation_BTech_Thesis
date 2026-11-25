# Iteration 16 — Lagrangian endpoint pricing with best-of-k measured moves and a ratcheting WNS floor in the post-stock TNS-recovery phase

cluster: `setup_strategy`

# Iteration 16 plan: Lagrangian endpoint pricing for the post-stock TNS-recovery phase

## Observation

- **The champion (iteration 13) is the only accepted change.** It keeps the stock LEGACY loop unchanged. Then `SetupLegacyPolicy::runTnsRecovery()` (`SetupLegacyPolicy.cc:445`) ranks shared drivers once per round and tries up to 3 moves on each of the top 50. It keeps a move only if measured TNS improves and WNS stays at or above a **fixed** floor `wns_floor`. That floor is captured once (lines 476–481) and never raised.
- **Two failure patterns repeat across iterations:**
  - **In-loop changes perturb the stock trajectory.** Iterations 8, 9, 12 and 15 all lost WNS on AES and JPEG, with drops of 1.9–18.7 ps.
  - **The fixed floor gives back WNS that recovery already earned.** In iteration 14, Ibex lost 5.2 ps WNS versus the champion while gaining 9.4 ns TNS. In iteration 15 the evaluator found the same floor problem.
- **The remaining slack has two different shapes:**
  - **JPEG:** the five worst endpoints are deep arithmetic cones (20–22 stages, HA/FA/AOI cells), each with its own bottleneck. The champion's shared-driver ranking always favours the most widely shared driver, so it rarely reaches these cones. JPEG TNS moved only −32.4 → −31.15 ns.
  - **Ibex:** every one of the ten worst paths still goes through `_26153_/ZN` (fanout 943). Recovery keeps spending trials on the same driver. Ibex output endpoints `instr_addr_o[22..30]` were also allowed to regress, because acceptance only looks at global WNS and TNS.
- **Static ranking is the common weakness.** "Count × summed negative slack, recomputed each round" has no memory of which endpoints stay violated after repeated attempts. It cannot redirect effort from a saturated shared driver to independent deep cones.

## Cluster choice and why

**setup_strategy.** Rotation allows it: the last three iterations were setup, sizing, buffering.

- **Why not buffering:** a third buffering attempt would be either a retreat to iteration 15's idea or a re-implementation of it. Buffering has 0 accepts in 4 tries.
- **Why not sizing:** sizing has 0 accepts in 5 tries.
- **Why setup_strategy:** it is the only cluster with a win, and the evidence points at a *decision procedure*, not at a move generator. The problems are how recovery picks targets, how it accepts moves, and when it stops.
- **Constraint respected:** the change stays strictly post-stock (dead end 13) and leaves the generators untouched.

## Hypothesis

**Problem.** Post-stock recovery picks targets with a myopic, memoryless shared-driver score and accepts moves against a fixed WNS floor. As a result it:
- over-invests in saturated shared drivers (Ibex `_26153_`);
- under-invests in independent deep cones (JPEG `mult_res[*]`);
- lets WNS gains slip away and lets individual endpoints regress (`instr_addr_o[22]`).

**Current heuristic.** Each round, score each driver as roughly (number of violating paths through it) × (summed negative slack) over up to 400 worst paths. Take the top 50 and try up to 3 moves on each. Accept the first move whose measured result has TNS better and WNS ≥ the stock-final WNS.

**New approach.** Recovery becomes a Lagrangian-relaxation / multiplicative-weights loop priced by endpoint:

1. **Endpoint multipliers.** Each violating endpoint *e* gets a multiplier λ_e, initialised to `slack_e / WNS`, so it lies in (0, 1].
2. **Driver score.** A driver *d* scores Σ_{e ∈ fanout-cone endpoints of d} λ_e · gain_est(d). Endpoints are deduplicated through reconvergence by walking each endpoint's worst path once.
3. **Multiplier update after each round.** Endpoints still violating get λ_e ← λ_e · (1 + η · |slack_e| / |WNS|) with η = 0.5. Endpoints whose slack did not improve over the round are doubled further. λ is then normalised so that Σλ = number of violators.
   - Effect: endpoints that resist cheap shared-driver fixes gain price. After 2–3 rounds the ranking moves from the Ibex fanout-943 trunk to JPEG's private HA/FA cones.
   - This is the LR subgradient idea applied to target selection, not to sizing.
4. **Best-of-k acceptance instead of first improving move.** For each chosen driver, measure every legal candidate from the existing generators (size-up, swap-pins, clone, split-load) from the same journal checkpoint. Commit the candidate with the best λ-weighted TNS gain. It must also pass two checks:
   - **(a) Ratcheting WNS floor:** floor = max(stock-final WNS, best WNS committed so far in recovery). This is the rule from iteration 15.
   - **(b) Per-endpoint veto:** no endpoint with λ_e above the median may lose more than 2 ps. This stops currently passing high-price endpoints from becoming violating.
5. **Budget.** The fixed "top 50 × 3 attempts" is replaced by a trial budget of 600 measured trials or 6 rounds per design, whichever comes first. Recovery stops early after a round with zero commits.

**Why WNS and TNS should improve:**
- **Ratchet:** WNS can only go up during recovery. This targets the 1.3–5.2 ps WNS losses seen in iterations 14 and 15.
- **λ pricing:** budget spreads to endpoints the champion never reached (JPEG deep cones, AES `sa*_sr` local slew). Expected effect is JPEG TNS gains well beyond champion's +1.25 ns, with WNS moving on JPEG specifically, since its worst endpoints get priced up.
- **Best-of-k:** removes the first-improving-move bias.
- **Stock trajectory:** stays byte-identical, so the AES and gcd stock gains are kept.

**Trigger estimate.**

| Design | Stock moves | Champion recovery commits | Planned recovery trials | Trials / stock moves |
|---|---:|---:|---:|---:|
| AES | 2,078 | 22 | ≥150 | ≈7% |
| Ibex | 172 | 30 | ≥200 | >100% |
| JPEG | 399 | 39 | ≥200 | — |

- All recovery target choices are new decisions by construction.
- AES clears the 5% bar on measured decisions. Ibex and JPEG exceed it by a wide margin.
- Expected commits are 40–80 per design, about double the champion's.

**Risks:**
- **Runtime.** The iteration-8 timeout came from uncapped measured search. Mitigations: hard trial cap, per-phase timer printed, and `estimate_parasitics`-incremental STA only.
- **Over-concentration.** λ could pile onto a few unrepairable endpoints. Mitigations: normalisation and a per-endpoint cap on λ.
- **Veto too strict.** The per-endpoint veto could block useful moves on AES. It will be measured through a rejection counter.
- **Legalisation.** Gains may not survive final detailed placement.

**How it shows in the path report:**
- Ibex top-10 paths no longer all share `_26153_`, or WNS improves while they still do.
- `instr_addr_o[22]` is not violating.
- JPEG `mult_res[18]` endpoints move toward −0.080 ns.
- Recovery WNS logs are monotone.

## Implementation sketch

- **`src/policy/SetupLegacyPolicy.cc` / `.hh`, `runTnsRecovery()`:**
  - Replace the per-round driver ranking with `priceEndpoints()` (λ init and update) and `rankDriversByPrice()`.
  - Replace the first-improving acceptance with `evaluateBestOfK(driver)`. It loops over the existing generators (`SizeUpGenerator`, `SwapPinsGenerator`, `CloneGenerator`, `SplitLoadGenerator`), each under its own journal begin/restore, and keeps the best.
  - Make `wns_floor` a ratchet that updates after each commit.
  - Add `endpointVetoOk()`, which uses a slack snapshot of above-median-λ endpoints taken before each trial.
- **No edits** to generators, `SetupLegacyBase.cc`, or the stock loop body (lines before 62).
- **Counters**, printed as `RSZ_EVOLVE ... fired=`:
  - `lr_rounds`, `lr_trials`, `lr_kept`, `lr_rejected_wns`, `lr_rejected_veto`, `lr_rejected_tns`
  - `lr_rank_changed_vs_static` (how often the λ ranking's top-50 differs from the champion ranking)
  - `lr_floor_final_ps`, `lr_phase_ms`
  - stock-phase move counts, to prove the stock phase is byte-identical
- **Determinism:** all maps are keyed by vertex id, not by pointer.

## Success criteria

- **Score vs champion ≥ +0.0020.** In practice this means at least one of:
  - JPEG TNS ≤ −30.0 ns with WNS ≥ −0.0853 ns;
  - Ibex TNS ≤ −38 ns with WNS ≥ −0.0742 ns.
- **No design loses WNS versus the champion.** The ratchet guarantees this before legalisation.
- **Counters:**
  - `lr_rank_changed_vs_static` is above 0 in at least 50% of rounds on JPEG and Ibex.
  - `lr_kept` is at least 1.5× the champion's `bottleneck_kept`.
- **Runtime:** JPEG recovery phase under 300 s.

## Fallback if it fails

- **If WNS holds but TNS gain is small:** pricing isn't redirecting effort. Inspect `lr_rank_changed_vs_static`.
  - If it is low, raise η. This is justified only because η is the lever on how far effort moves away from shared drivers.
  - If it is high but commits are few, the move menu is the limit. Next iteration should then switch to the timing_model cluster (better gain estimates) rather than widening search.
- **If post-legalisation losses appear:** the next rule is to re-time after placement inside recovery.

```json
{"cluster": "setup_strategy", "title": "Lagrangian endpoint pricing with best-of-k measured moves and a ratcheting WNS floor in the post-stock TNS-recovery phase", "hypothesis": "The champion's post-stock recovery (runTnsRecovery) ranks drivers with a memoryless shared-driver score and accepts the first improving move against a fixed stock-WNS floor, so it saturates on Ibex's fanout-943 driver, rarely reaches JPEG's independent deep arithmetic cones, and gives back WNS (iterations 14, 15). Replace it with a multiplicative-weights Lagrangian loop: each violating endpoint carries a price lambda_e that grows while it stays violated, drivers are ranked by the lambda-weighted sum over their deduplicated downstream endpoints, and each chosen driver gets best-of-k measured evaluation across the existing size/swap/clone/split generators from one journal checkpoint. Commits must satisfy a ratcheting WNS floor max(stock-final, best-so-far) and a per-endpoint veto protecting high-price endpoints. The stock loop stays byte-identical; a 600-trial or 6-round budget bounds runtime, avoiding iteration 8's timeout.", "files": ["src/policy/SetupLegacyPolicy.cc", "src/policy/SetupLegacyPolicy.hh"], "evidence_iterations": [13, 8, 14, 15, 9], "success_criteria": "Score vs champion >= +0.002 with no design losing WNS vs champion; JPEG TNS <= -30.0 ns or Ibex TNS <= -38 ns; lr_rank_changed_vs_static > 0 in >= 50% of JPEG/Ibex rounds; JPEG recovery < 300 s", "risk": "Measured best-of-k trials may exceed the runtime cap or yield gains that do not survive detailed placement; the per-endpoint veto may over-block AES moves.", "rule_updates": "Post-stock recovery phases must use a ratcheting WNS floor (never below the best committed recovery WNS) and print lr/bottleneck counters showing how often target ranking differs from the champion's static ranking."}
```
