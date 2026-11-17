# Feedback for iteration 6 (0006_buffering, cluster buffering)

```
vs champion:
REJECT  score=-0.00039
  nangate45/gcd      WNS -0.1742 -> -0.1742 ns  TNS -7.626 -> -7.626 ns  score +0.00000
  nangate45/aes      WNS -0.1083 -> -0.1112 ns  TNS -14.773 -> -15.027 ns  score -0.00236
  nangate45/ibex     WNS -0.2994 -> -0.2978 ns  TNS -416.273 -> -401.637 ns  score +0.00119
  ! score -0.00039 below required gain +0.00200

vs baseline:
ACCEPT  score=-0.00039
  nangate45/gcd      WNS -0.1742 -> -0.1742 ns  TNS -7.626 -> -7.626 ns  score +0.00000
  nangate45/aes      WNS -0.1083 -> -0.1112 ns  TNS -14.773 -> -15.027 ns  score -0.00236
  nangate45/ibex     WNS -0.2994 -> -0.2978 ns  TNS -416.273 -> -401.637 ns  score +0.00119
```

The filesystem is read-only, so I could not save `feedback.md`. Its contents follow.

# 1. Outcome

**REJECT against champion.** Score **−0.00039**, versus required **+0.00200**: shortfall **0.00239**. The authoritative baseline verdict is **ACCEPT**, with the same negative score; this does not qualify the candidate for champion promotion.

Deltas below are candidate minus reference; positive means improvement. Reference values are identical in the supplied champion and baseline comparisons.

| Design | WNS reference → candidate (ns) | ΔWNS (ns) | TNS reference → candidate (ns) | ΔTNS (ns) | Score |
|---|---:|---:|---:|---:|---:|
| nangate45/gcd | −0.1742 → −0.1742 | 0.0000 | −7.626 → −7.626 | 0.000 | +0.00000 |
| nangate45/aes | −0.1083 → −0.1112 | −0.0029 | −14.773 → −15.027 | −0.254 | −0.00236 |
| nangate45/ibex | −0.2994 → −0.2978 | +0.0016 | −416.273 → −401.637 | +14.636 | +0.00119 |

All six unit targets and ten smoke tests passed. Both replicates produced identical timing results for each design. Post-repair hold violations, reported DRVs, and placement violations were zero.

# 2. Did the hypothesis do what it predicted?

**Partially in aggregate timing; the proposed repair mechanism is unverified.**

The patch changes `src/rsz/src/move/BufferGenerator.cc` eligibility and its header documentation. It preserves the low-fanout branch and existing net protection checks. Above the cutoff, it requires setup analysis, a known transition, clock exclusion, and two distinct immediate loads with finite negative slack. It does not change the rebuffer search or commit policy.

Observed effects:

- **Ibex:** WNS improves approximately **1.6 ps**, only **8%** of the candidate hypothesis’s **20 ps** target. TNS magnitude falls **3.52%**, exceeding its **1%** target.
- **Matched Ibex endpoints:** `rf_reg[982]`, `[854]`, and `[662]` improve only **0.518, 0.517, and 0.518 ps** against reference. Output improvements are larger: `instr_addr_o[30]` gains **6.216 ps** and `[31]` gains **12.715 ps**.
- **AES:** WNS worsens **2.9 ps** and TNS magnitude increases **1.72%**. Ten matched endpoints regress; ten other endpoints enter the sampled worst list.
- **GCD:** Timing and sampled endpoint results match reference exactly, consistent with preserved low-fanout behavior.

Ibex logs report **67 inserted buffers**, **149 upsizes**, and **5 clones**. These totals do not identify newly eligible drivers or establish that repairs on fanout **22/31/45** survived rollback and legalization. Multiple move types also prevent assigning the timing gain specifically to rebuffering.

The **114.640 ps** pre-repair improvement at Ibex `rf_reg[982]` includes the entire repair flow. Its attributable candidate-versus-reference improvement is **0.518 ps**. The larger pre-repair delta is not evidence for this patch.

# 3. Where the remaining negative slack comes from

The five worst reported endpoints across all designs are all Ibex register-file inputs. Endpoint names below share prefix `gen_regfile_ff.register_file_i.`.

| Endpoint | Post slack (ns) | Likely cause | Relevant move types | Why the current algorithm likely left it |
|---|---:|---|---|---|
| `rf_reg[982]$_DFFE_PN0P_/D` | −0.297844 | Deep data logic; possible shared load and weak-driver contribution | SizeUp, SwapPins, data Buffer, Clone/SplitLoad | Eligibility changes do not shorten the logic cone; retained high-fanout data repair is unverified |
| `rf_reg[854]$_DFFE_PN0P_/D` | −0.297291 | Same shared cone | Same moves | Only +0.517 ps versus reference; common delay remains |
| `rf_reg[662]$_DFFE_PN0P_/D` | −0.297208 | Same shared cone | Same moves | Only +0.518 ps versus reference; common delay remains |
| `rf_reg[566]$_DFFE_PN0P_/D` | −0.297206 | Same shared cone | Same moves | Newly present in sampled list; no matched reference delta establishes repair efficacy |
| `rf_reg[694]$_DFFE_PN0P_/D` | −0.297116 | Same shared cone | Same moves | Newly present in sampled list; no matched reference delta establishes repair efficacy |

All five reports contain **36 stages**, repeated MUX cells, **six FA_X1 cells and one HA_X1**, and shared slow drivers including `NOR3_X1@_20302_/ZN` and `AOI221_X2@_19754_/ZN`. This supports investigating accumulated data-cell delay and weak drive.

**Attribution limitation:** these paths start at `clk_i` and include a DFF after `AND2_X1@_26153_/ZN`. The reported **fanout 943** and worst slew may therefore belong to the launch-clock portion. They do not establish a 943-load data bottleneck or clock skew. Separate launch clock, data, and capture clock before selecting a repair. Preserve clock exclusion.

The raw slew numbers have no validated unit interpretation here. The `io_constrained` tag also does not prove an IO constraint dominates these register endpoints. Long-wire dominance and clock skew require delay decomposition.

Other design limits:

- **GCD:** worst slack **−0.174175 ns**, 16 stages, maximum fanout 8. Investigate existing sizing/pin-swap opportunities around `_604_` and `_950_`; expanding eligibility above 20 cannot directly address these reported fanouts.
- **AES:** worst slack **−0.111187 ns**, with slow XOR/XNOR and AOI drivers. These need driver/arc and placement analysis; fanout qualification alone does not address their delay.

# 4. Regressions

Matched endpoint changes from `paths_attribution.json`; negative deltas mean worse slack.

| Design | Endpoint | Δslack (ps) |
|---|---|---:|
| AES | `sa23_sr[5]$_DFF_P_/D` | −5.965 |
| AES | `sa33_sr[1]$_DFF_P_/D` | −5.576 |
| AES | `sa33_sr[3]$_DFF_P_/D` | −2.246 |
| AES | `sa32_sr[7]$_DFF_P_/D` | −6.743 |
| AES | `sa23_sr[7]$_DFF_P_/D` | −3.701 |
| AES | `sa02_sr[7]$_DFF_P_/D` | −2.946 |
| AES | `u0.u1.d[7]$_DFF_P_/D` | −1.877 |
| AES | `sa23_sr[4]$_DFF_P_/D` | −2.097 |
| AES | `sa20_sr[7]$_DFF_P_/D` | −1.322 |
| AES | `sa23_sr[0]$_DFF_P_/D` | −0.318 |
| Ibex | `instr_addr_o[28]` | −0.492 |
| Ibex | `data_addr_o[30]` | −0.269 |
| Ibex | `instr_addr_o[20]` | −3.219 |
| Ibex | `data_addr_o[28]` | −0.269 |
| Ibex | `instr_addr_o[12]` | −0.011 |
| Ibex | `data_addr_o[20]` | −3.269 |

Probable mechanisms are altered shared loading/topology, changed subsequent move selection, and placement displacement. Preserving low-fanout eligibility does not preserve the resulting optimization trajectory.

Legalization sensitivity is directly visible. AES ends repair near **−0.108 ns WNS / −14.7 ns TNS**, then measures **−0.111187 / −15.026695 ns** after legalization. Ibex similarly moves from approximately **−0.295 / −397.2 ns** to **−0.297844 / −401.637078 ns**. Both legalized HPWL totals rise about **2%**. These observations support placement sensitivity, but do not isolate its contribution relative to reference.

# 5. Recommendation for the next iteration

**Recommended cluster: buffering.** Continue with a constrained, attributable experiment; do not promote this patch.

1. **Trace retained repairs before changing eligibility further.** Record driver, transition, fanout, qualifying loads, attempt result, rollback/commit status, and final topology for the 22/31/45 targets. Measure at least two downstream endpoints after legalization. Distinguish candidate application from final retention.
2. **Make high-fanout acceptance account for collateral and legalization losses.** Compare affected endpoint WNS/TNS before and after each retained topology change, including sibling branches. Add a checkpoint that can reject a batch whose gains disappear after legalization. AES is the required regression case.
3. **Improve branch selection only after establishing the failing stage.** If newly eligible searches produce no retained repair, inspect required-time-aware partitioning and tree pruning in `Rebuffer.cc`; prioritize shared negative-slack data branches while limiting added upstream capacitance. Compare identical target sets to isolate topology changes.
4. **Switch to sizing if data-delay decomposition shows cell delay dominates.** Target shared FA/MUX/NOR/AOI arcs in the Ibex register-file cone. Compare sizing and buffering from the same starting design rather than combining changes initially.

**Do not try again:** another blanket fanout-cutoff expansion justified only by aggregate buffer counts or whole-flow pre/post timing. This candidate already shows that broader eligibility can improve Ibex TNS while losing the overall score.

```json
{
  "recommended_cluster": "buffering",
  "dominant_cause": "deep_logic",
  "lesson": "High-fanout eligibility reduced Ibex TNS by 3.52% but failed promotion because AES regressed and retained repairs on the intended drivers were not established.",
  "dead_end": "Do not repeat fanout eligibility expansion without retained-driver attribution and post-legalization collateral checks.",
  "good_changes": [
    "src/rsz/src/move/BufferGenerator.cc preserves low-fanout eligibility, net protections, and clock exclusion; GCD timing remained identical.",
    "The eligibility-only candidate reduced Ibex TNS by 14.636 ns, but the specific retained rebuffer mechanism remains unverified."
  ],
  "bad_changes": [
    "src/rsz/src/move/BufferGenerator.cc enables high-fanout candidates by default without demonstrating post-legalization benefit across affected branches; AES WNS and TNS regressed.",
    "Reusing BufferCandidate and Rebuffer unchanged did not establish retained repairs on fanout-22/31/45 targets or meet the 20 ps Ibex WNS target."
  ],
  "files_to_revisit": [
    "src/rsz/src/move/BufferGenerator.cc",
    "src/rsz/src/move/BufferCandidate.cc",
    "src/rsz/src/Rebuffer.cc",
    "src/rsz/src/Optimizer.cc",
    "src/rsz/src/RepairTargetCollector.cc"
  ],
  "files_to_avoid": [
    "src/rsz/src/move/BufferGenerator.hh"
  ]
}
```
