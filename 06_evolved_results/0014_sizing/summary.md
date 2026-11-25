# Candidate `0014_sizing`

tier A, variant `stressed`, replicates 1, evaluated 2026-11-25T14:26:32Z

## Verdict vs champion

```
REJECT  score=-0.00038
  nangate45/gcd      WNS -0.0222 -> -0.0222 ns  TNS -0.342 -> -0.339 ns  score +0.00001
  nangate45/aes      WNS -0.0241 -> -0.0241 ns  TNS -0.999 -> -0.992 ns  score +0.00000
  nangate45/ibex     WNS -0.0742 -> -0.0794 ns  TNS -44.399 -> -34.985 ns  score -0.00089
  nangate45/jpeg     WNS -0.0853 -> -0.0866 ns  TNS -31.151 -> -31.095 ns  score -0.00064
  ! score -0.00038 below required gain +0.00200
```

## Verdict vs baseline (stock OpenROAD)

```
ACCEPT  score=+0.00168
  nangate45/gcd      WNS -0.0234 -> -0.0222 ns  TNS -0.475 -> -0.339 ns  score +0.00401
  nangate45/aes      WNS -0.0258 -> -0.0241 ns  TNS -1.141 -> -0.992 ns  score +0.00124
  nangate45/ibex     WNS -0.0794 -> -0.0794 ns  TNS -65.665 -> -34.985 ns  score +0.00138
  nangate45/jpeg     WNS -0.0866 -> -0.0866 ns  TNS -32.403 -> -31.095 ns  score +0.00009
```

## Did the new logic run? (RSZ_EVOLVE counters per design)

- nangate45/gcd: {'window_dp_examined': 224, 'window_dp_with_gain': 131, 'window_joint_changed_vs_greedy': 122, 'window_dp_stages_changed': 354, 'window_dp_trials': 131, 'window_dp_kept': 6, 'window_dp_rejected_wns': 67, 'window_dp_rejected_tns': 58, 'bottleneck_rounds': 5, 'bottleneck_drivers_ranked': 873, 'bottleneck_trials': 325, 'bottleneck_kept': 17, 'bottleneck_rejected_wns': 27, 'bottleneck_rejected_tns': 54}  | moves {'resized': 31, 'pins_swapped': 5} vs baseline {'resized': 24, 'pins_swapped': 1}
- nangate45/aes: {'window_dp_examined': 226, 'window_dp_with_gain': 75, 'window_joint_changed_vs_greedy': 40, 'window_dp_stages_changed': 138, 'window_dp_trials': 75, 'window_dp_kept': 11, 'window_dp_rejected_wns': 20, 'window_dp_rejected_tns': 44, 'bottleneck_rounds': 5, 'bottleneck_drivers_ranked': 5852, 'bottleneck_trials': 279, 'bottleneck_kept': 25, 'bottleneck_rejected_wns': 17, 'bottleneck_rejected_tns': 24}  | moves {'buffers_removed': 7, 'buffers_inserted': 486, 'resized': 1403, 'pins_swapped': 138, 'cloned': 70} vs baseline {'buffers_removed': 7, 'buffers_inserted': 481, 'resized': 1388, 'pins_swapped': 132, 'cloned': 70}
- nangate45/ibex: {'window_dp_examined': 67, 'window_dp_with_gain': 41, 'window_joint_changed_vs_greedy': 30, 'window_dp_stages_changed': 89, 'window_dp_trials': 41, 'window_dp_kept': 15, 'window_dp_rejected_wns': 14, 'window_dp_rejected_tns': 12, 'bottleneck_rounds': 4, 'bottleneck_drivers_ranked': 2844, 'bottleneck_trials': 245, 'bottleneck_kept': 30, 'bottleneck_rejected_wns': 16, 'bottleneck_rejected_tns': 78}  | moves {'resized': 151, 'pins_swapped': 17, 'cloned': 9} vs baseline {'resized': 149, 'pins_swapped': 14, 'cloned': 9}
- nangate45/jpeg: {'window_dp_examined': 80, 'window_dp_with_gain': 75, 'window_joint_changed_vs_greedy': 68, 'window_dp_stages_changed': 215, 'window_dp_trials': 75, 'window_dp_kept': 14, 'window_dp_rejected_wns': 49, 'window_dp_rejected_tns': 12, 'bottleneck_rounds': 2, 'bottleneck_drivers_ranked': 8437, 'bottleneck_trials': 151, 'bottleneck_kept': 34, 'bottleneck_rejected_wns': 74, 'bottleneck_rejected_tns': 13}  | moves {'resized': 296, 'pins_swapped': 121} vs baseline {'resized': 282, 'pins_swapped': 117}

## Worst paths after repair (candidate)

### nangate45/gcd

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `dpath.a_reg.out[5]$_DFFE_PP_/D` | -0.022241 | -0.023594 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 2 | `dpath.a_reg.out[4]$_DFFE_PP_/D` | -0.021947 | -0.024712 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 3 | `dpath.a_reg.out[6]$_DFFE_PP_/D` | -0.020864 | -0.023613 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 4 | `dpath.a_reg.out[9]$_DFFE_PP_/D` | -0.019842 | -0.022439 | 14 | 5 | 28771000.0 | slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 5 | `dpath.a_reg.out[1]$_DFFE_PP_/D` | -0.019633 | -0.021732 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 6 | `dpath.a_reg.out[3]$_DFFE_PP_/D` | -0.019447 | -0.022508 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 7 | `dpath.a_reg.out[10]$_DFFE_PP_/D` | -0.019306 | None | 12 | 3 | 25047002.0 | slow_slew | NAND2_X1@_578_/ZN (slew 25047002.0), XNOR2_X2@_763_/ZN (slew 23333000.0) |
| 8 | `dpath.a_reg.out[2]$_DFFE_PP_/D` | -0.01859 | -0.021079 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 9 | `dpath.a_reg.out[0]$_DFFE_PP_/D` | -0.018172 | None | 14 | 5 | 28771000.0 | slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 10 | `dpath.a_reg.out[8]$_DFFE_PP_/D` | -0.01802 | -0.022223 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |

Tag histogram: slow_slew=38, io_constrained=18, high_fanout=13, near_zero=10

vs reference: improved 15, regressed 5, new in worst list 3, gone 3
- regressed `resp_msg[9]`: +0.0032 -> +0.0008
- regressed `resp_msg[8]`: +0.0212 -> +0.0043
- regressed `resp_msg[5]`: +0.0160 -> +0.0138
- regressed `resp_msg[3]`: +0.0255 -> +0.0225
- regressed `resp_msg[2]`: +0.0617 -> +0.0610
- improved `dpath.a_reg.out[5]$_DFFE_PP_/D`: -0.0234 -> -0.0222
- improved `dpath.a_reg.out[4]$_DFFE_PP_/D`: -0.0226 -> -0.0219
- improved `dpath.a_reg.out[6]$_DFFE_PP_/D`: -0.0218 -> -0.0209
- improved `dpath.a_reg.out[12]$_DFFE_PP_/D`: -0.0213 -> -0.0177
- improved `dpath.a_reg.out[10]$_DFFE_PP_/D`: -0.0211 -> -0.0193

### nangate45/aes

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `sa10_sr[3]$_DFF_P_/D` | -0.024128 | None | 15 | 4 | 75224000.0 | slow_slew | OAI33_X1@_19597_/ZN (slew 75224000.0), XNOR2_X2@_14869_/ZN (slew 50566000.0) |
| 2 | `sa23_sr[0]$_DFF_P_/D` | -0.024078 | -0.064183 | 15 | 7 | 63210004.0 | slow_slew | OAI33_X1@_15856_/ZN (slew 63210004.0), XOR2_X2@_13050_/Z (slew 61395004.0) |
| 3 | `sa23_sr[5]$_DFF_P_/D` | -0.023272 | -0.063612 | 16 | 7 | 61833004.0 | slow_slew | OAI33_X1@_16121_/ZN (slew 61833004.0), XOR2_X2@_13050_/Z (slew 61395004.0) |
| 4 | `sa23_sr[7]$_DFF_P_/D` | -0.023234 | None | 16 | 7 | 61395004.0 | slow_slew | XOR2_X2@_13050_/Z (slew 61395004.0), NOR2_X2@_13121_/ZN (slew 38508004.0) |
| 5 | `sa11_sr[3]$_DFF_P_/D` | -0.023147 | None | 14 | 5 | 53805004.0 | slow_slew | XOR2_X2@_16432_/Z (slew 53805004.0), AOI222_X2@_16838_/ZN (slew 46332004.0) |
| 6 | `sa20_sr[7]$_DFF_P_/D` | -0.022404 | None | 13 | 7 | 57840004.0 | slow_slew | XOR2_X2@_14133_/Z (slew 57838000.0), AOI222_X2@_14250_/ZN (slew 42426004.0) |
| 7 | `sa23_sr[4]$_DFF_P_/D` | -0.021825 | -0.067301 | 14 | 7 | 61395004.0 | slow_slew | XOR2_X2@_13050_/Z (slew 61395004.0), NOR2_X1@_13133_/ZN (slew 46299000.0) |
| 8 | `sa01_sr[5]$_DFF_P_/D` | -0.020935 | None | 14 | 8 | 68560000.0 | high_fanout slow_slew | XOR2_X2@_12864_/Z (slew 68557000.0), OAI221_X1@_19328_/ZN (slew 38466000.0) |
| 9 | `sa03_sr[7]$_DFF_P_/D` | -0.020641 | None | 13 | 22 | 64911004.0 | high_fanout slow_slew | XOR2_X2@_13680_/Z (slew 64911004.0), AOI221_X1@_13791_/ZN (slew 44726000.0) |
| 10 | `sa33_sr[3]$_DFF_P_/D` | -0.019829 | None | 17 | 7 | 55729004.0 | slow_slew | XNOR2_X2@_11708_/ZN (slew 55725004.0), OAI222_X1@_14671_/ZN (slew 49353000.0) |

Tag histogram: slow_slew=40, io_constrained=20, high_fanout=7

vs reference: improved 13, regressed 1, new in worst list 3, gone 3
- regressed `sa10_sr[3]$_DFF_P_/D`: -0.0227 -> -0.0241
- improved `sa33_sr[3]$_DFF_P_/D`: -0.0258 -> -0.0198
- improved `sa11_sr[3]$_DFF_P_/D`: -0.0247 -> -0.0231
- improved `sa23_sr[0]$_DFF_P_/D`: -0.0242 -> -0.0241
- improved `sa23_sr[5]$_DFF_P_/D`: -0.0234 -> -0.0233
- improved `sa23_sr[7]$_DFF_P_/D`: -0.0233 -> -0.0232

### nangate45/ibex

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `gen_regfile_ff.register_file_i.rf_reg[703]$_DFFE_PN0P_/D` | -0.079444 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57538000.0) |
| 2 | `gen_regfile_ff.register_file_i.rf_reg[607]$_DFFE_PN0P_/D` | -0.079054 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57538000.0) |
| 3 | `gen_regfile_ff.register_file_i.rf_reg[831]$_DFFE_PN0P_/D` | -0.078826 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57538000.0) |
| 4 | `gen_regfile_ff.register_file_i.rf_reg[799]$_DFFE_PN0P_/D` | -0.078808 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57538000.0) |
| 5 | `gen_regfile_ff.register_file_i.rf_reg[895]$_DFFE_PN0P_/D` | -0.078752 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57538000.0) |
| 6 | `gen_regfile_ff.register_file_i.rf_reg[191]$_DFFE_PN0P_/D` | -0.078746 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57538000.0) |
| 7 | `gen_regfile_ff.register_file_i.rf_reg[671]$_DFFE_PN0P_/D` | -0.078708 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57538000.0) |
| 8 | `gen_regfile_ff.register_file_i.rf_reg[735]$_DFFE_PN0P_/D` | -0.078591 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57538000.0) |
| 9 | `gen_regfile_ff.register_file_i.rf_reg[63]$_DFFE_PN0P_/D` | -0.078572 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57538000.0) |
| 10 | `gen_regfile_ff.register_file_i.rf_reg[927]$_DFFE_PN0P_/D` | -0.078463 | None | 39 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57538000.0) |

Tag histogram: slow_slew=61, high_fanout=60, deep_logic=40, io_constrained=40, near_zero=7

vs reference: improved 15, regressed 15, new in worst list 4, gone 4
- regressed `gen_regfile_ff.register_file_i.rf_reg[703]$_DFFE_PN0P_/D`: -0.0794 -> -0.0794
- regressed `gen_regfile_ff.register_file_i.rf_reg[607]$_DFFE_PN0P_/D`: -0.0790 -> -0.0791
- regressed `gen_regfile_ff.register_file_i.rf_reg[831]$_DFFE_PN0P_/D`: -0.0788 -> -0.0788
- regressed `gen_regfile_ff.register_file_i.rf_reg[799]$_DFFE_PN0P_/D`: -0.0788 -> -0.0788
- regressed `gen_regfile_ff.register_file_i.rf_reg[895]$_DFFE_PN0P_/D`: -0.0787 -> -0.0788
- improved `instr_addr_o[31]`: -0.0573 -> -0.0481
- improved `instr_addr_o[30]`: -0.0522 -> -0.0475
- improved `instr_addr_o[28]`: -0.0280 -> -0.0166
- improved `instr_addr_o[29]`: +0.0021 -> +0.0112
- improved `instr_addr_o[23]`: +0.0106 -> +0.0335

### nangate45/jpeg

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.086591 | None | 21 | 12 | 35598000.0 | deep_logic high_fanout slow_slew | HA_X1@_115901_/S (slew 35598000.0), FA_X1@_108721_/S (slew 24679000.0) |
| 2 | `fdct_zigzag.dct_mod.dct_block_5.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.085302 | None | 22 | 15 | 36248000.0 | deep_logic high_fanout slow_slew | DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0), HA_X1@_114238_/S (slew 27197000.0) |
| 3 | `fdct_zigzag.dct_mod.dct_block_7.dct_unit_4.macu.mult_res[15]$_DFFE_PP_/D` | -0.084674 | None | 20 | 15 | 40669004.0 | deep_logic high_fanout slow_slew | HA_X1@_115122_/S (slew 40669004.0), DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0) |
| 4 | `fdct_zigzag.dct_mod.dct_block_4.dct_unit_7.macu.mult_res[16]$_DFFE_PP_/D` | -0.084582 | None | 21 | 12 | 36248000.0 | deep_logic high_fanout slow_slew | DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0), HA_X1@_114347_/S (slew 32198002.0) |
| 5 | `fdct_zigzag.dct_mod.dct_block_7.dct_unit_2.macu.mult_res[18]$_DFFE_PP_/D` | -0.084084 | -0.111903 | 22 | 17 | 39042000.0 | deep_logic high_fanout slow_slew | FA_X1@_109354_/S (slew 39042000.0), HA_X1@_115805_/S (slew 37304000.0) |
| 6 | `fdct_zigzag.dct_mod.dct_block_5.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D` | -0.08352 | None | 21 | 15 | 39442000.0 | deep_logic high_fanout slow_slew | OAI221_X1@_095447_/ZN (slew 39442000.0), DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0) |
| 7 | `fdct_zigzag.dct_mod.dct_block_1.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D` | -0.083192 | None | 23 | 17 | 38575004.0 | deep_logic high_fanout slow_slew | HA_X1@_115070_/S (slew 38575004.0), AOI21_X1@_081689_/ZN (slew 34703004.0) |
| 8 | `fdct_zigzag.dct_mod.dct_block_3.dct_unit_3.macu.mult_res[16]$_DFFE_PP_/D` | -0.083034 | None | 23 | 17 | 35726000.0 | deep_logic high_fanout slow_slew | HA_X1@_115059_/S (slew 35726000.0), OAI21_X1@_089120_/ZN (slew 33784000.0) |
| 9 | `fdct_zigzag.dct_mod.dct_block_1.dct_unit_2.macu.mult_res[18]$_DFFE_PP_/D` | -0.083015 | None | 23 | 17 | 38575004.0 | deep_logic high_fanout slow_slew | HA_X1@_115070_/S (slew 38575004.0), AOI21_X1@_081689_/ZN (slew 34703004.0) |
| 10 | `fdct_zigzag.dct_mod.dct_block_2.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D` | -0.0827 | None | 22 | 9 | 36248000.0 | deep_logic high_fanout slow_slew | DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0), HA_X1@_114253_/S (slew 34149000.0) |

Tag histogram: slow_slew=60, high_fanout=40, io_constrained=40, deep_logic=20

vs reference: improved 6, regressed 5, new in worst list 6, gone 6
- regressed `fdct_zigzag.dct_mod.dct_block_1.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D`: -0.0831 -> -0.0832
- regressed `fdct_zigzag.dct_mod.dct_block_3.dct_unit_3.macu.mult_res[16]$_DFFE_PP_/D`: -0.0827 -> -0.0830
- regressed `fdct_zigzag.dct_mod.dct_block_1.dct_unit_2.macu.mult_res[18]$_DFFE_PP_/D`: -0.0829 -> -0.0830
- regressed `fdct_zigzag.dct_mod.dct_block_2.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D`: -0.0825 -> -0.0827
- regressed `fdct_zigzag.dct_mod.ddin[3]$_DFFE_PN0P_/RN`: +0.6102 -> +0.6101
- improved `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D`: -0.0866 -> -0.0866
- improved `fdct_zigzag.dct_mod.dct_block_2.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D`: -0.0843 -> -0.0827
- improved `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D`: -0.0834 -> -0.0817
- improved `fdct_zigzag.dct_mod.dct_block_6.dct_unit_6.macu.mult_res[16]$_DFFE_PP_/D`: -0.0823 -> -0.0812
- improved `fdct_zigzag.dct_mod.dct_block_7.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D`: -0.0819 -> -0.0813

## Gates

```
gates: PASS
  unit  PASSED   //src/rsz/test:TestInsertBuffer
  unit  PASSED   //src/rsz/test:TestNestedJournal
  unit  PASSED   //src/rsz/test:TestPreChecks
  unit  PASSED   //src/rsz/test:TestResizer
  unit  PASSED   //src/rsz/test:TestSkewBudget
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
