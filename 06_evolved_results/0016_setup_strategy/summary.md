# Candidate `0016_setup_strategy`

tier A, variant `stressed`, replicates 1, evaluated 2026-11-25T16:12:21Z

## Verdict vs champion

```
REJECT  score=-0.00014
  nangate45/gcd      WNS -0.0222 -> -0.0222 ns  TNS -0.342 -> -0.335 ns  score +0.00014
  nangate45/aes      WNS -0.0241 -> -0.0242 ns  TNS -0.999 -> -1.019 ns  score -0.00005
  nangate45/ibex     WNS -0.0742 -> -0.0746 ns  TNS -44.399 -> -57.068 ns  score -0.00067
  nangate45/jpeg     WNS -0.0853 -> -0.0853 ns  TNS -31.151 -> -30.637 ns  score +0.00003
  ! score -0.00014 below required gain +0.00200
```

## Verdict vs baseline (stock OpenROAD)

```
ACCEPT  score=+0.00192
  nangate45/gcd      WNS -0.0234 -> -0.0222 ns  TNS -0.475 -> -0.335 ns  score +0.00413
  nangate45/aes      WNS -0.0258 -> -0.0242 ns  TNS -1.141 -> -1.019 ns  score +0.00119
  nangate45/ibex     WNS -0.0794 -> -0.0746 ns  TNS -65.665 -> -57.068 ns  score +0.00160
  nangate45/jpeg     WNS -0.0866 -> -0.0853 ns  TNS -32.403 -> -30.637 ns  score +0.00077
```

## Did the new logic run? (RSZ_EVOLVE counters per design)

- nangate45/gcd: {'bottleneck_rounds': 6, 'bottleneck_drivers_ranked': 949, 'bottleneck_trials': 469, 'bottleneck_kept': 21, 'bottleneck_rejected_wns': 47, 'bottleneck_rejected_tns': 32, 'lr_rank_changed_vs_static': 6, 'lr_price_updates': 139, 'lr_best_of_k_evals': 443, 'lr_best_not_first': 1, 'lr_endpoint_veto_blocked': 39, 'lr_wns_floor_ratchets': 1}  | moves {'resized': 44, 'pins_swapped': 1} vs baseline {'resized': 24, 'pins_swapped': 1}
- nangate45/aes: {'bottleneck_rounds': 6, 'bottleneck_drivers_ranked': 7017, 'bottleneck_trials': 370, 'bottleneck_kept': 12, 'bottleneck_rejected_wns': 18, 'bottleneck_rejected_tns': 12, 'lr_rank_changed_vs_static': 6, 'lr_price_updates': 526, 'lr_best_of_k_evals': 354, 'lr_best_not_first': 4, 'lr_endpoint_veto_blocked': 8, 'lr_wns_floor_ratchets': 0}  | moves {'buffers_removed': 7, 'buffers_inserted': 489, 'resized': 1408, 'pins_swapped': 134, 'cloned': 70} vs baseline {'buffers_removed': 7, 'buffers_inserted': 481, 'resized': 1388, 'pins_swapped': 132, 'cloned': 70}
- nangate45/ibex: {'bottleneck_rounds': 6, 'bottleneck_drivers_ranked': 4463, 'bottleneck_trials': 526, 'bottleneck_kept': 39, 'bottleneck_rejected_wns': 32, 'bottleneck_rejected_tns': 105, 'lr_rank_changed_vs_static': 1, 'lr_price_updates': 7368, 'lr_best_of_k_evals': 479, 'lr_best_not_first': 6, 'lr_endpoint_veto_blocked': 11, 'lr_wns_floor_ratchets': 5}  | moves {'buffers_inserted': 84, 'resized': 153, 'pins_swapped': 13, 'cloned': 12} vs baseline {'resized': 149, 'pins_swapped': 14, 'cloned': 9}
- nangate45/jpeg: {'bottleneck_rounds': 5, 'bottleneck_drivers_ranked': 21183, 'bottleneck_trials': 600, 'bottleneck_kept': 57, 'bottleneck_rejected_wns': 241, 'bottleneck_rejected_tns': 52, 'lr_rank_changed_vs_static': 5, 'lr_price_updates': 2421, 'lr_best_of_k_evals': 543, 'lr_best_not_first': 17, 'lr_endpoint_veto_blocked': 24, 'lr_wns_floor_ratchets': 1}  | moves {'resized': 324, 'pins_swapped': 119, 'cloned': 1} vs baseline {'resized': 282, 'pins_swapped': 117}

## Worst paths after repair (candidate)

### nangate45/gcd

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `dpath.a_reg.out[5]$_DFFE_PP_/D` | -0.022215 | -0.023594 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 2 | `dpath.a_reg.out[4]$_DFFE_PP_/D` | -0.02192 | -0.024712 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 3 | `dpath.a_reg.out[6]$_DFFE_PP_/D` | -0.020838 | -0.023613 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 4 | `dpath.a_reg.out[9]$_DFFE_PP_/D` | -0.019816 | -0.022439 | 14 | 5 | 28771000.0 | slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 5 | `dpath.a_reg.out[1]$_DFFE_PP_/D` | -0.019607 | -0.021732 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 6 | `dpath.a_reg.out[3]$_DFFE_PP_/D` | -0.019421 | -0.022508 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 7 | `dpath.a_reg.out[2]$_DFFE_PP_/D` | -0.018564 | -0.021079 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 8 | `dpath.a_reg.out[0]$_DFFE_PP_/D` | -0.018146 | None | 14 | 5 | 28771000.0 | slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 9 | `dpath.a_reg.out[8]$_DFFE_PP_/D` | -0.017994 | -0.022223 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 10 | `dpath.a_reg.out[7]$_DFFE_PP_/D` | -0.017792 | None | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |

Tag histogram: slow_slew=38, io_constrained=18, high_fanout=12, near_zero=12

vs reference: improved 15, regressed 7, new in worst list 1, gone 1
- regressed `dpath.a_reg.out[14]$_DFFE_PP_/D`: -0.0165 -> -0.0168
- regressed `dpath.a_reg.out[13]$_DFFE_PP_/D`: -0.0155 -> -0.0156
- regressed `resp_msg[14]`: -0.0119 -> -0.0122
- regressed `resp_msg[13]`: -0.0064 -> -0.0065
- regressed `resp_msg[9]`: +0.0032 -> +0.0032
- improved `dpath.a_reg.out[5]$_DFFE_PP_/D`: -0.0234 -> -0.0222
- improved `dpath.a_reg.out[4]$_DFFE_PP_/D`: -0.0226 -> -0.0219
- improved `dpath.a_reg.out[6]$_DFFE_PP_/D`: -0.0218 -> -0.0208
- improved `dpath.a_reg.out[12]$_DFFE_PP_/D`: -0.0213 -> -0.0177
- improved `dpath.a_reg.out[10]$_DFFE_PP_/D`: -0.0211 -> -0.0167

### nangate45/aes

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `sa23_sr[0]$_DFF_P_/D` | -0.024186 | -0.064183 | 15 | 7 | 63210004.0 | slow_slew | OAI33_X1@_15856_/ZN (slew 63210004.0), XOR2_X2@_13050_/Z (slew 61395004.0) |
| 2 | `sa10_sr[3]$_DFF_P_/D` | -0.024128 | None | 15 | 4 | 75224000.0 | slow_slew | OAI33_X1@_19597_/ZN (slew 75224000.0), XNOR2_X2@_14869_/ZN (slew 50566000.0) |
| 3 | `sa11_sr[3]$_DFF_P_/D` | -0.02377 | None | 14 | 5 | 53805004.0 | slow_slew | XOR2_X2@_16432_/Z (slew 53805004.0), AOI222_X2@_16838_/ZN (slew 46332004.0) |
| 4 | `sa23_sr[5]$_DFF_P_/D` | -0.02338 | -0.063612 | 16 | 7 | 61833004.0 | slow_slew | OAI33_X1@_16121_/ZN (slew 61833004.0), XOR2_X2@_13050_/Z (slew 61395004.0) |
| 5 | `sa23_sr[7]$_DFF_P_/D` | -0.023341 | None | 16 | 7 | 61395004.0 | slow_slew | XOR2_X2@_13050_/Z (slew 61395004.0), NOR2_X2@_13121_/ZN (slew 38508004.0) |
| 6 | `sa20_sr[7]$_DFF_P_/D` | -0.022404 | None | 13 | 7 | 57840004.0 | slow_slew | XOR2_X2@_14133_/Z (slew 57838000.0), AOI222_X2@_14250_/ZN (slew 42426004.0) |
| 7 | `sa23_sr[4]$_DFF_P_/D` | -0.021932 | -0.067301 | 14 | 7 | 61395004.0 | slow_slew | XOR2_X2@_13050_/Z (slew 61395004.0), NOR2_X1@_13133_/ZN (slew 46299000.0) |
| 8 | `sa23_sr[6]$_DFF_P_/D` | -0.021842 | None | 16 | 5 | 48755004.0 | slow_slew | XOR2_X2@_13069_/Z (slew 48754000.0), AOI221_X1@_16154_/ZN (slew 42610004.0) |
| 9 | `sa33_sr[3]$_DFF_P_/D` | -0.02122 | None | 14 | 15 | 52588004.0 | high_fanout slow_slew | NOR2_X1@_11830_/ZN (slew 52588004.0), XOR2_X2@_11720_/Z (slew 47052000.0) |
| 10 | `sa02_sr[7]$_DFF_P_/D` | -0.021099 | None | 17 | 12 | 42551000.0 | high_fanout slow_slew | AOI221_X1@_13394_/ZN (slew 42551000.0), NOR2_X1@_13271_/ZN (slew 41300000.0) |

Tag histogram: slow_slew=40, io_constrained=20, high_fanout=8

vs reference: improved 6, regressed 2, new in worst list 3, gone 3
- regressed `sa10_sr[3]$_DFF_P_/D`: -0.0227 -> -0.0241
- regressed `sa02_sr[4]$_DFF_P_/D`: -0.0196 -> -0.0196
- improved `sa33_sr[3]$_DFF_P_/D`: -0.0258 -> -0.0212
- improved `sa11_sr[3]$_DFF_P_/D`: -0.0247 -> -0.0238
- improved `sa01_sr[5]$_DFF_P_/D`: -0.0231 -> -0.0209
- improved `sa20_sr[7]$_DFF_P_/D`: -0.0227 -> -0.0224
- improved `sa02_sr[7]$_DFF_P_/D`: -0.0211 -> -0.0211

### nangate45/ibex

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `gen_regfile_ff.register_file_i.rf_reg[703]$_DFFE_PN0P_/D` | -0.074627 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57412000.0) |
| 2 | `gen_regfile_ff.register_file_i.rf_reg[607]$_DFFE_PN0P_/D` | -0.074236 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57412000.0) |
| 3 | `gen_regfile_ff.register_file_i.rf_reg[831]$_DFFE_PN0P_/D` | -0.074009 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57412000.0) |
| 4 | `gen_regfile_ff.register_file_i.rf_reg[799]$_DFFE_PN0P_/D` | -0.073991 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57412000.0) |
| 5 | `gen_regfile_ff.register_file_i.rf_reg[895]$_DFFE_PN0P_/D` | -0.073935 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57412000.0) |
| 6 | `gen_regfile_ff.register_file_i.rf_reg[191]$_DFFE_PN0P_/D` | -0.073929 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57412000.0) |
| 7 | `gen_regfile_ff.register_file_i.rf_reg[671]$_DFFE_PN0P_/D` | -0.073891 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57412000.0) |
| 8 | `gen_regfile_ff.register_file_i.rf_reg[735]$_DFFE_PN0P_/D` | -0.073773 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57412000.0) |
| 9 | `gen_regfile_ff.register_file_i.rf_reg[63]$_DFFE_PN0P_/D` | -0.073755 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57412000.0) |
| 10 | `gen_regfile_ff.register_file_i.rf_reg[927]$_DFFE_PN0P_/D` | -0.073646 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57412000.0) |

Tag histogram: slow_slew=61, high_fanout=60, deep_logic=40, io_constrained=40, near_zero=9

vs reference: improved 15, regressed 14, new in worst list 3, gone 3
- regressed `instr_addr_o[31]`: -0.0573 -> -0.0612
- regressed `instr_addr_o[22]`: +0.0001 -> -0.0157
- regressed `instr_addr_o[29]`: +0.0021 -> -0.0019
- regressed `instr_addr_o[23]`: +0.0106 -> +0.0033
- regressed `instr_addr_o[24]`: +0.0305 -> +0.0044
- improved `gen_regfile_ff.register_file_i.rf_reg[703]$_DFFE_PN0P_/D`: -0.0794 -> -0.0746
- improved `gen_regfile_ff.register_file_i.rf_reg[607]$_DFFE_PN0P_/D`: -0.0790 -> -0.0742
- improved `gen_regfile_ff.register_file_i.rf_reg[831]$_DFFE_PN0P_/D`: -0.0788 -> -0.0740
- improved `gen_regfile_ff.register_file_i.rf_reg[799]$_DFFE_PN0P_/D`: -0.0788 -> -0.0740
- improved `gen_regfile_ff.register_file_i.rf_reg[895]$_DFFE_PN0P_/D`: -0.0787 -> -0.0739

### nangate45/jpeg

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `fdct_zigzag.dct_mod.dct_block_5.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.085302 | None | 22 | 15 | 36248000.0 | deep_logic high_fanout slow_slew | DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0), HA_X1@_114238_/S (slew 27197000.0) |
| 2 | `fdct_zigzag.dct_mod.dct_block_7.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D` | -0.085151 | None | 22 | 11 | 36709000.0 | deep_logic high_fanout slow_slew | OAI221_X1@_102791_/ZN (slew 36709000.0), AOI21_X1@_102809_/ZN (slew 29170002.0) |
| 3 | `fdct_zigzag.dct_mod.dct_block_7.dct_unit_4.macu.mult_res[15]$_DFFE_PP_/D` | -0.084674 | None | 20 | 15 | 40669004.0 | deep_logic high_fanout slow_slew | HA_X1@_115122_/S (slew 40669004.0), DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0) |
| 4 | `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.084179 | None | 20 | 12 | 28983002.0 | deep_logic high_fanout slow_slew | HA_X1@_115442_/S (slew 28983002.0), FA_X1@_108721_/S (slew 26319002.0) |
| 5 | `fdct_zigzag.dct_mod.dct_block_5.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D` | -0.08352 | None | 21 | 15 | 39442000.0 | deep_logic high_fanout slow_slew | OAI221_X1@_095447_/ZN (slew 39442000.0), DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0) |
| 6 | `fdct_zigzag.dct_mod.dct_block_7.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.082993 | -0.116082 | 19 | 11 | 27432002.0 | deep_logic high_fanout slow_slew | HA_X1@_114583_/S (slew 27432002.0), FA_X1@_108402_/S (slew 23565000.0) |
| 7 | `fdct_zigzag.dct_mod.dct_block_6.dct_unit_2.macu.mult_res[17]$_DFFE_PP_/D` | -0.082747 | None | 22 | 12 | 36265000.0 | deep_logic high_fanout slow_slew | HA_X1@_114934_/S (slew 36265000.0), OAI21_X1@_100284_/ZN (slew 29509002.0) |
| 8 | `fdct_zigzag.dct_mod.dct_block_2.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D` | -0.082579 | None | 22 | 9 | 36248000.0 | deep_logic high_fanout slow_slew | DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0), HA_X1@_114253_/S (slew 34149000.0) |
| 9 | `fdct_zigzag.dct_mod.dct_block_6.dct_unit_6.macu.mult_res[16]$_DFFE_PP_/D` | -0.0823 | None | 20 | 34 | 37642000.0 | deep_logic high_fanout slow_slew | NOR3_X1@_098208_/ZN (slew 37642000.0), HA_X1@_114368_/S (slew 33179000.0) |
| 10 | `fdct_zigzag.dct_mod.dct_block_1.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.081818 | None | 21 | 15 | 39746004.0 | deep_logic high_fanout slow_slew | HA_X1@_113788_/S (slew 39746004.0), DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0) |

Tag histogram: slow_slew=60, high_fanout=40, io_constrained=40, deep_logic=20

vs reference: improved 15, regressed 5, new in worst list 10, gone 10
- regressed `fdct_zigzag.dct_mod.dct_block_7.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D`: -0.0819 -> -0.0852
- regressed `fdct_zigzag.dct_mod.dct_block_2.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D`: -0.0825 -> -0.0826
- regressed `fdct_zigzag.dct_mod.ddcnt$_DFFE_PN1P_/SN`: +0.6002 -> +0.6001
- regressed `fdct_zigzag.dct_mod.ddin[7]$_DFFE_PN0P_/RN`: +0.6084 -> +0.6083
- regressed `fdct_zigzag.dct_mod.ddin[4]$_DFFE_PN0P_/RN`: +0.6223 -> +0.6223
- improved `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D`: -0.0866 -> -0.0842
- improved `fdct_zigzag.dct_mod.dct_block_2.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D`: -0.0843 -> -0.0806
- improved `fdct_zigzag.dct_mod.dct_block_6.dct_unit_6.macu.mult_res[16]$_DFFE_PP_/D`: -0.0823 -> -0.0823
- improved `fdct_zigzag.dct_mod.dddcnt$_DFFE_PN1P_/SN`: +0.6003 -> +0.6004
- improved `fdct_zigzag.dct_mod.ddin[5]$_DFFE_PN0P_/RN`: +0.6005 -> +0.6007

## Gates

```
gates: PASS
  unit  PASSED   //src/rsz/test:TestInsertBuffer
  unit  PASSED   //src/rsz/test:TestNestedJournal
  unit  PASSED   //src/rsz/test:TestPreChecks
  unit  PASSED   //src/rsz/test:TestSkewBudget
  unit  PASSED   //src/rsz/test:TestResizer
  unit  PASSED   //src/rsz/test:cpp_tests
  smoke ok       repair_setup1
  smoke ok       repair_setup2
  smoke ok       repair_setup3
  smoke ok       repair_setup4
  smoke ok       repair_setup5
  smoke ok       repair_hold1
  smoke ok       repair_hold2
  smoke ok       repair_hold3
  smoke ok       repair_design1
  smoke ok       repair_design2
```
