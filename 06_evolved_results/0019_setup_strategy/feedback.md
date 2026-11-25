# Feedback for iteration 19 (0019_setup_strategy, cluster setup_strategy)

```
vs champion:
REJECT  score=-0.00145
  nangate45/gcd      WNS -0.0222 -> -0.0229 ns  TNS -0.342 -> -0.378 ns  score -0.00159
  nangate45/aes      WNS -0.0241 -> -0.0258 ns  TNS -0.999 -> -1.141 ns  score -0.00124
  nangate45/ibex     WNS -0.0742 -> -0.0794 ns  TNS -44.399 -> -65.665 ns  score -0.00227
  nangate45/jpeg     WNS -0.0853 -> -0.0866 ns  TNS -31.151 -> -31.878 ns  score -0.00070
  ! score -0.00145 below required gain +0.00200

vs baseline:
ACCEPT  score=+0.00061
  nangate45/gcd      WNS -0.0234 -> -0.0229 ns  TNS -0.475 -> -0.378 ns  score +0.00240
  nangate45/aes      WNS -0.0258 -> -0.0258 ns  TNS -1.141 -> -1.141 ns  score +0.00000
  nangate45/ibex     WNS -0.0794 -> -0.0794 ns  TNS -65.665 -> -65.665 ns  score +0.00000
  nangate45/jpeg     WNS -0.0866 -> -0.0866 ns  TNS -32.403 -> -31.878 ns  score +0.00003
```

The filesystem is read-only, so I could not save `feedback.md`. Its content follows.

## 1. Outcome

**REJECT vs champion:** score **−0.00145**, missing the required +0.00200 gain by **0.00345**. Baseline verdict: ACCEPT, score **+0.00061**.

Deltas are candidate minus comparator; positive means improvement. Values use the authoritative rounded measurements.

| Design | Candidate WNS (ns) | Candidate TNS (ns) | ΔWNS vs champion (ps) | ΔTNS vs champion (ns) | ΔWNS vs baseline (ps) | ΔTNS vs baseline (ns) |
|---|---:|---:|---:|---:|---:|---:|
| gcd | −0.0229 | −0.378 | −0.7 | −0.036 | +0.5 | +0.097 |
| aes | −0.0258 | −1.141 | −1.7 | −0.142 | 0.0 | 0.000 |
| ibex | −0.0794 | −65.665 | −5.2 | −21.266 | 0.0 | 0.000 |
| jpeg | −0.0866 | −31.878 | −1.3 | −0.727 | 0.0 | +0.525 |

Ibex accounts for **95.9%** of the total 22.171 ns TNS deficit against champion. All six unit targets and ten smoke checks passed; these checks did not establish replay correctness on the measured Ibex case.

## 2. Did the hypothesis do what it predicted?

**Only partially on JPEG; no observed coupled benefit on Ibex.**

| Design | Ranked seeds¹ | Single/pair trials | Committed single/pair | WNS rejections | Replay failures |
|---|---:|---:|---:|---:|---:|
| gcd | 344 | 4 / 3 | 1 / 0 | 4 | 0 |
| aes | 1,177 | 0 / 0 | 0 / 0 | 0 | 0 |
| ibex | 781 | 8 / 10 | 0 / 0 | 3 | 1 |
| jpeg | 8,343 | 4 / 4 | 0 / 1 | 6 | 0 |

¹Accumulated across rounds, not necessarily unique seeds.

- **Coupled resizing:** JPEG committed one pair and reduced baseline TNS magnitude by **1.62%**, with unchanged WNS. Ibex committed nothing after a replay failure and finished at baseline timing. The central prediction—recovering Ibex coupled gains—was not demonstrated.
- **Worst-path repair:** JPEG’s worst endpoints remain 19–23-stage multiplier chains. Its worst slack remains **−86.622 ps**. Aggregate TNS improvement did not reach the limiting path.
- **Seed effectiveness:** AES ranked 1,177 seeds but produced zero measured trials. Ranking is disconnected from move availability. The inspected Nangate45 typical library contains FA_X1 and HA_X1, with no stronger FA/HA variants; direct upsizing of these arithmetic cells is unavailable.
- **Clock exclusion:** Every `beam_clock_arcs_skipped` counter is zero. This does not establish that filtering failed: traversal starts at `expanded.startIndex()`, which can already omit launch-clock arcs. The attribution report still includes Ibex `_26153_` before launch CK/Q; its fanout 943 must not be treated as data-path fanout.
- **Acceptance:** Thirteen trials failed the WNS floor; none reached a recorded endpoint-guard rejection. The guard therefore has no demonstrated protective effect here.
- **Replacement cost:** `runTnsRecovery` now invokes only `runBeamRecovery`; the champion’s greedy recovery is left unreferenced. The floor protects post-stock timing, not champion timing, so it cannot prevent losing the champion’s recovery gains.

## 3. Where the remaining negative slack comes from

The five worst endpoints across all designs are **all JPEG endpoints**. Below, each suffix follows `fdct_zigzag.dct_mod.` and ends in `$_DFFE_PP_/D`.

| Endpoint suffix | Slack (ps) | Structure and likely cause | Applicable moves | Why recovery likely missed it |
|---|---:|---|---|---|
| `dct_block_6.dct_unit_4.macu.mult_res[18]` | −86.622 | 20 stages; four FA_X1 outputs; HA `_115442_` and FA `_108721_` have worst reported slew. **Deep logic**, secondary weak drive. | Resize surrounding INV/AOI/OAI stages; swap legal arithmetic inputs; reduce FA/HA output load. | Arithmetic cells lack stronger variants; eight measured JPEG trials provide little coverage of thousands of ranked seeds. |
| `dct_block_5.dct_unit_2.macu.mult_res[16]` | −85.652 | 23 stages; four FA_X1 outputs; HA `_114387_`, OAI21 `_096477_`; max fanout 50. **Deep logic**, secondary fanout/load. | Split or buffer the actual fanout-50 data branch; pair surrounding driver resizing with load reduction. | A two-stage local sequence may not address the shared launch-distribution load and arithmetic chain together. Six JPEG WNS rejections constrain changes. |
| `dct_block_5.dct_unit_4.macu.mult_res[18]` | −85.302 | 22 stages; four FA_X1 outputs; slow launch DFFR_X2 Q and HA `_114238_`; max fanout 15. **Deep logic plus launch-drive load.** | Legal launch-flop resizing, branch buffering/cloning, surrounding-stage resizing. | Highest-delay arithmetic seeds may be immovable; partners are retained from only the first path that introduced each seed. |
| `dct_block_7.dct_unit_4.macu.mult_res[15]` | −84.674 | 20 stages; four FA_X1 outputs; HA `_115122_` has especially slow slew; shared launch Q; max fanout 15. **Deep logic plus weak drive.** | Reduce HA load; resize adjacent gates; repair shared launch distribution. | HA_X1 cannot be directly upsized; one committed pair did not change this limiting cone. |
| `dct_block_2.dct_unit_4.macu.mult_res[18]` | −84.263 | 19 stages; four FA_X1 outputs; HA `_115515_`, NOR3_X2 `_106305_`; max fanout 12. **Deep logic**, secondary slew. | Resize NOR3/adjacent gates where alternatives exist; load splitting and legal pin swaps. | Fixed top-eight seed selection can omit feasible surrounding stages while retaining high-ranked arithmetic cells without size alternatives. |

All five paths report **zero clock skew**. They are register-to-register paths; IO constraints are not the indicated cause. Wire-delay dominance is unproven because these reports lack a cell/net delay breakdown. Reported slew values have anomalous scaling and should not be interpreted directly as physical picoseconds.

Ibex remains the largest aggregate recovery opportunity: 1,484 violating endpoints and −65.665 ns TNS. Its deep data chains remain unchanged after zero beam commits.

## 4. Regressions

**Against baseline:** the sampled endpoint diff records no matched-endpoint regressions. GCD improves 12 endpoints; AES and Ibex are unchanged. JPEG has four entries entering and four leaving the worst list; list turnover alone does not prove regression.

**Against champion:** every design loses WNS and TNS. Champion endpoint-level slacks are unavailable, so the aggregate losses cannot be assigned to named endpoints reliably.

The probable mechanism is **foregone recovery**, especially on Ibex, rather than demonstrated destructive beam commits: the candidate removes greedy recovery, AES generates no trials, and Ibex aborts after replay failure. JPEG’s one accepted pair recovers less TNS than champion recovery.

A separate implementation gap remains: the endpoint guard snapshots only endpoints below **+50 ps**. An endpoint initially above that window could cross below −1 ps without belonging to the protected set. No measured regression here establishes that this happened.

## 5. Recommendation for the next iteration

1. **`setup_strategy`: fix deterministic sequence replay first.** Store concrete candidate operations, selected replacement cells, pins, and partner moves. `Cand` currently stores names and a move-type exclusion, then reruns generators during replay. Audit journal restoration of generator/committer state and compare trial versus replay operations and timing. Require zero Ibex replay failures before evaluating wider search.

2. **`setup_strategy`: preserve champion recovery as a measured alternative.** Run greedy and beam from equivalent restored checkpoints, then retain the better eligible result. Keep the champion result when beam produces no commits or fails replay. Ibex’s **21.266 ns** champion TNS advantage is the primary target.

3. **`setup_strategy`: select feasible, diverse seeds.** Continue scanning until eight seeds with legal candidates are found, rather than stopping at eight ranked pins. Log unavailable size alternatives, failed target creation, and failed candidate generation. Enumerate partners from multiple covered paths and apply the data-arc filter to partners too. Target AES’s zero trials and JPEG’s immovable FA/HA seeds.

4. **`setup_strategy`: make endpoint protection complete.** Compare stable endpoint identities and before/after slack for all endpoints affected by a sequence, including those initially above +50 ps. Retain the ratcheting WNS floor; do not loosen it to compensate for replay or coverage defects.

**Do not repeat:** replacing champion greedy recovery with the same top-eight, regenerated-move beam while Ibex replay remains unresolved.

```json
{
  "recommended_cluster": "setup_strategy",
  "dominant_cause": "deep_logic",
  "lesson": "Measured depth-2 recovery improved JPEG baseline TNS by 0.525 ns but lost champion recovery because AES generated no trials and Ibex failed replay.",
  "dead_end": "Do not replace champion greedy recovery with a fixed top-eight beam that regenerates moves during replay and cannot resize its dominant FA_X1/HA_X1 seeds.",
  "good_changes": [
    "src/rsz/src/policy/SetupLegacyPolicy.cc: measured pair evaluation committed one JPEG pair with unchanged baseline WNS",
    "src/rsz/src/policy/SetupLegacyPolicy.cc: measured single-move recovery improved GCD baseline TNS by 0.097 ns"
  ],
  "bad_changes": [
    "src/rsz/src/policy/SetupLegacyPolicy.cc: runTnsRecovery bypasses champion runGreedyTnsRecovery",
    "src/rsz/src/policy/SetupLegacyPolicy.cc: Cand stores pin names and exclusions rather than exact replayable operations",
    "src/rsz/src/policy/SetupLegacyPolicy.cc: fixed top-eight seed selection produced zero AES trials",
    "src/rsz/src/policy/SetupLegacyPolicy.cc: endpoint protection omits endpoints initially above +50 ps"
  ],
  "files_to_revisit": [
    "src/rsz/src/policy/SetupLegacyPolicy.cc",
    "src/rsz/src/policy/SetupLegacyPolicy.hh",
    "src/rsz/src/policy/SetupLegacyBase.cc",
    "src/rsz/src/MoveCommitter.cc",
    "src/rsz/src/move/SizeUpGenerator.cc"
  ],
  "files_to_avoid": []
}
```
