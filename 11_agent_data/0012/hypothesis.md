# Iteration 12 — TNS-weighted lexicographic acceptance (WNS guard band + design TNS gain) replacing endpoint-only slack acceptance in the LEGACY repair loop

cluster: `setup_strategy`

# Iteration 12 plan: TNS-weighted acceptance with a WNS guard band in the LEGACY setup loop

## Observation

- **Across 9 valid experiments, only setup-strategy changes moved Ibex a lot.**
  - Iteration 8 used measured WNS/TNS selection and Ibex TNS improved by 57.554 ns (−65.67 → −8.11).
  - Iteration 9 used shared-criticality ranking and Ibex TNS improved by 34.327 ns.
  - Buffering and sizing gained less than 0.15 ns of TNS on any design, even when iteration 10 changed 23 sizing choices and iteration 11 changed the buffer-tree choice at the root.
- **Both setup-strategy wins lost on the other designs, for different reasons.**
  - Iteration 8 tried every move with a full timing refresh. JPEG timed out at 1800 s, and AES got 16.8 ps worse WNS because only one winner was allowed per pass.
  - Iteration 9 changed *which targets* were attacked. That changed JPEG's first target on 92.8% of passes, its resizes fell from 282 to 54, and AES and JPEG got worse.
- **What I take from this:** shared-cone TNS on Ibex is real and reachable. Changing the target order or searching exhaustively damages the AES and JPEG trajectories. The part neither attempt isolated is the **acceptance test**. Today a move is kept only if it improves the slack of the endpoint currently being repaired (the WNS view). A move on Ibex's `_26153_` cone (fanout 943, 35 stages) that helps hundreds of endpoints but barely moves the current one is rolled back.
- **The remaining slack is mostly long arithmetic chains (deep logic):** JPEG's half-adder/full-adder MAC chains and Ibex's `AND2_X1 _26153_` trunk. The same generators (sizing, cloning, pin swaps) are the right moves for these. The open question is which of their outcomes the loop keeps.

## Cluster choice and why

**setup_strategy.** The last two iterations were sizing (10) and buffering (11), so rotating clusters points here. Setup strategy was also last used in iteration 9, so this is not a third time in a row.

This is not a narrower version of iteration 8 or 9; it changes a different decision procedure:
- Target ranking stays stock (iteration 9 changed it).
- Move generation stays stock: the first improving candidate, no exhaustive search, no extra timing refresh per trial (iteration 8 did exhaustive trials).
- Only the **accept/reject rule after each speculative commit** changes.

Buffering was considered and set aside: full 3-D Pareto retention costs a lot and its upper bound is small. Iteration 11's V reranking moved TNS by at most 0.15 ns.

## Hypothesis

- **Problem:** Shared-cone moves that improve many violating endpoints are discarded because acceptance looks only at the current endpoint's slack. Moves that slightly help the current endpoint while hurting many side paths are kept. This is the AES pattern in iterations 7 and 11, where the moves look locally safe but TNS gets worse.
- **Current heuristic:** In `SetupLegacyPolicy` (with `SetupLegacyBase`), each move is applied inside a `MoveCommitter` journal, timing is updated, and the move is kept (`commitTrackedMoves`) only if the targeted endpoint's slack improves. Otherwise it is undone (`abortJournalScope`). Design TNS is never read in that decision.
- **New approach:** **Lexicographic WNS-band / TNS acceptance.** After the incremental timing update that already happens, read design WNS and TNS. `Sta::totalNegativeSlack` and `worstSlack` are kept incrementally by OpenSTA, so no extra propagation is needed. Accept the move if both hold:
  - (a) design WNS does not get worse by more than ε_W = 1 ps, and the targeted endpoint does not get worse by more than ε_W; and
  - (b) a combined gain is positive: ΔTNS + λ·ΔWNS_endpoint > 0, with λ = (number of violating endpoints) / 4.
  - The WNS term therefore dominates on designs with few violators, such as gcd. A rule like this only works if one constant is the lever, and here it is λ: it sets how much the current endpoint counts against the rest of the design.
  - A stock-accepted move that **lowers** TNS by more than 2× its endpoint gain is rejected.
  - Exact reduction to stock: on any design or pass where the TNS term is unchanged (ΔTNS equals the endpoint's own Δ), the decision is identical to stock.
- **Why WNS/TNS should improve:**
  - On Ibex, moves on the shared trunk are kept, so the cone-level TNS gain from iterations 8 and 9 should appear without reordering targets.
  - On AES, the moves behind the regressions seen in iterations 7, 9 and 11 (local gain, side-path TNS loss) get vetoed.
  - On JPEG, the target order and move mix stay stock, avoiding the iteration 9 collapse to 54 resizes.
- **Risks:**
  - Accepting moves that do not improve the current endpoint could stall progress on that endpoint and loop. Mitigation: per-endpoint repair caps stay stock, and a TNS-only acceptance counts against `max_repairs_per_pass`.
  - Gains measured before detailed placement may not survive it. That is unchanged from stock, but there will now be more marginal moves.
  - Small WNS loss within the 1 ps band.

## Implementation sketch

- **`src/policy/SetupLegacyPolicy.cc` / `.hh`, and the acceptance helper in `src/policy/SetupLegacyBase.cc` / `.hh` (wherever the endpoint slack is compared before `commitTrackedMoves` / `abortJournalScope`):**
  - Snapshot `wns0` and `tns0` (design-wide, setup, current scene) together with the endpoint slack before the move.
  - After the move, compute `dW_ep`, `dWNS` and `dTNS`, then apply the rule above.
  - Keep stock behaviour available behind `RSZ_EVOLVE_STOCK_ACCEPT=1` so the gates can run stock if needed.
- **Instrumentation:** emit `RSZ_EVOLVE` counters (required by iterations 9 and 11) from the policy's end-of-phase report path:
  - `evaluated`
  - `stock_accept`
  - `new_accept`
  - `flipped_to_accept` (TNS-driven)
  - `flipped_to_reject` (TNS veto)
  - `sum_dTNS_flipped`
  - the printed ε_W and λ

  Print zeros as well. Print from the code path that is known to run, the same `SetupLegacyBase` route that worked in iteration 9, not from `RebufferMtGenerator`.
- No changes to generators, target ranking or `RepairSetupAnalysisTarget.cc`.

## Trigger estimate

Every acceptance decision is re-evaluated: about 2,078 on AES, 172 on Ibex, 399 on JPEG and 25 on gcd. I expect 5–15% of them to flip:
- AES: about 100–300 decisions, mostly TNS vetoes.
- Ibex: about 10–30 decisions, mostly TNS-driven accepts on the `_26153_` cone.
- JPEG: about 20–60 decisions.

This is above the 5% threshold. The counters will measure the actual numbers.

## Success criteria

- Score ≥ +0.002 against the champion.
- Ibex TNS better than −55 ns (more than 10 ns gained), with WNS not worse.
- AES TNS no worse than −1.15 ns and WNS within 1 ps.
- JPEG finishes within the timeout, with TNS no worse than −32.6 ns.
- gcd identical or better.
- `RSZ_EVOLVE` counters present on all four designs, with `flipped_* > 0` on AES and Ibex.

## Fallback if it fails

- **Counters show flips but Ibex is unchanged:** the trunk moves are never generated, so the limit is generation, not acceptance. Next step is the timing_model cluster (slack budgets for the shared trunk).
- **AES regresses despite the vetoes:** the gains do not survive detailed placement. Add a rule that acceptance must be re-checked after placement, and switch cluster.
- **Do not** go back to reordering targets or exhaustive per-move search.

```json
{"cluster": "setup_strategy", "title": "TNS-weighted lexicographic acceptance (WNS guard band + design TNS gain) replacing endpoint-only slack acceptance in the LEGACY repair loop", "hypothesis": "Stock LEGACY repair keeps a speculative move only if the targeted endpoint's slack improves, so shared-cone moves that help many violating endpoints (Ibex _26153_ trunk) are rolled back while locally-helpful moves that hurt side paths (AES regressions in iters 7/9/11) are kept. Replace this with a lexicographic rule using OpenSTA's incrementally maintained design WNS/TNS: reject if design or endpoint WNS worsens by more than 1 ps, otherwise accept when dTNS + lambda*dSlack_endpoint > 0 (lambda = violators/4), and veto stock-accepted moves whose TNS loss exceeds 2x their endpoint gain. Target ranking and move generators stay stock, which avoids the trajectory collapse of iteration 9 and the exhaustive-search timeout of iteration 8. The rule reduces exactly to stock when the TNS change equals the endpoint's own change. Expect Ibex TNS to improve by more than 10 ns, AES TNS to stop regressing, and JPEG to stay near stock.", "files": ["src/policy/SetupLegacyPolicy.cc", "src/policy/SetupLegacyPolicy.hh", "src/policy/SetupLegacyBase.cc", "src/policy/SetupLegacyBase.hh"], "evidence_iterations": [8, 9, 11, 7], "success_criteria": "score >= +0.002; Ibex TNS > -55 ns with WNS not worse; AES TNS >= -1.15 ns and WNS within 1 ps; JPEG finishes within the timeout; RSZ_EVOLVE flip counters > 0 on AES and Ibex", "risk": "TNS-driven accepts may stall per-endpoint WNS progress or fail to survive detailed placement, causing small WNS losses inside the 1 ps band", "rule_updates": "Acceptance-rule changes must print evaluated/flipped_to_accept/flipped_to_reject counts and the summed predicted dTNS of flipped moves, and must leave target ranking and generators stock so the effect can be attributed."}
```

I didn't open the source this time, so two things are unconfirmed. The exact name of the acceptance function in `SetupLegacyPolicy` / `SetupLegacyBase` is my inference from the dossier; the coding agent should find the slack comparison before `commitTrackedMoves`. My claim that reading OpenSTA's WNS/TNS after each move is cheap, which is what keeps JPEG inside the timeout, is also unverified. The session is read-only, so I couldn't write the plan or the rule update into `10_agent_knowledge`; both are in the JSON above.
