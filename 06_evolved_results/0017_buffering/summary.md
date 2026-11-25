# Candidate `0017_buffering`

tier A, variant `stressed`, replicates 1, evaluated 2026-11-25T16:51:27Z

## Verdict vs champion

```
REJECT  score=+0.00000
  nangate45/gcd      WNS -0.0222 -> -0.0222 ns  TNS -0.342 -> -0.342 ns  score +0.00000
  nangate45/aes      WNS -0.0241 -> -0.0241 ns  TNS -0.999 -> -0.999 ns  score +0.00000
  nangate45/ibex     WNS -0.0742 -> -0.0742 ns  TNS -44.399 -> -44.399 ns  score +0.00000
  nangate45/jpeg     WNS -0.0853 -> -0.0853 ns  TNS -31.151 -> -31.151 ns  score +0.00000
  ! score +0.00000 below required gain +0.00200
```

## Verdict vs baseline (stock OpenROAD)

```
ACCEPT  score=+0.00206
  nangate45/gcd      WNS -0.0234 -> -0.0222 ns  TNS -0.475 -> -0.342 ns  score +0.00399
  nangate45/aes      WNS -0.0258 -> -0.0241 ns  TNS -1.141 -> -0.999 ns  score +0.00124
  nangate45/ibex     WNS -0.0794 -> -0.0742 ns  TNS -65.665 -> -44.399 ns  score +0.00227
  nangate45/jpeg     WNS -0.0866 -> -0.0853 ns  TNS -32.403 -> -31.151 ns  score +0.00074
```

## Did the new logic run? (RSZ_EVOLVE counters per design)

- nangate45/gcd: {'fanout_tree_built': 0, 'fanout_tree_buffers': 0, 'fanout_tree_sinks_isolated': 0, 'fanout_tree_stock_fallback': 0, 'bottleneck_rounds': 5, 'bottleneck_drivers_ranked': 874, 'bottleneck_trials': 328, 'bottleneck_kept': 17, 'bottleneck_rejected_wns': 22, 'bottleneck_rejected_tns': 56}  | moves {'resized': 37, 'pins_swapped': 4} vs baseline {'resized': 24, 'pins_swapped': 1}
- nangate45/aes: {'fanout_tree_built': 0, 'fanout_tree_buffers': 0, 'fanout_tree_sinks_isolated': 0, 'fanout_tree_stock_fallback': 0, 'bottleneck_rounds': 5, 'bottleneck_drivers_ranked': 5892, 'bottleneck_trials': 285, 'bottleneck_kept': 22, 'bottleneck_rejected_wns': 19, 'bottleneck_rejected_tns': 17}  | moves {'buffers_removed': 7, 'buffers_inserted': 486, 'resized': 1415, 'pins_swapped': 139, 'cloned': 70} vs baseline {'buffers_removed': 7, 'buffers_inserted': 481, 'resized': 1388, 'pins_swapped': 132, 'cloned': 70}
- nangate45/ibex: {'fanout_tree_built': 0, 'fanout_tree_buffers': 0, 'fanout_tree_sinks_isolated': 0, 'fanout_tree_stock_fallback': 2, 'bottleneck_rounds': 4, 'bottleneck_drivers_ranked': 2879, 'bottleneck_trials': 288, 'bottleneck_kept': 30, 'bottleneck_rejected_wns': 17, 'bottleneck_rejected_tns': 89}  | moves {'resized': 158, 'pins_swapped': 22, 'cloned': 10} vs baseline {'resized': 149, 'pins_swapped': 14, 'cloned': 9}
- nangate45/jpeg: {'fanout_tree_built': 0, 'fanout_tree_buffers': 0, 'fanout_tree_sinks_isolated': 0, 'fanout_tree_stock_fallback': 1, 'bottleneck_rounds': 2, 'bottleneck_drivers_ranked': 8425, 'bottleneck_trials': 169, 'bottleneck_kept': 34, 'bottleneck_rejected_wns': 77, 'bottleneck_rejected_tns': 12}  | moves {'resized': 308, 'pins_swapped': 123, 'cloned': 1} vs baseline {'resized': 282, 'pins_swapped': 117}

## Worst paths after repair (candidate)

### nangate45/gcd

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `dpath.a_reg.out[5]$_DFFE_PP_/D` | -0.022215 | -0.023594 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 2 | `dpath.a_reg.out[4]$_DFFE_PP_/D` | -0.02192 | -0.024712 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 3 | `dpath.a_reg.out[6]$_DFFE_PP_/D` | -0.020838 | -0.023613 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 4 | `dpath.a_reg.out[9]$_DFFE_PP_/D` | -0.019815 | -0.022439 | 14 | 5 | 28771000.0 | slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 5 | `dpath.a_reg.out[1]$_DFFE_PP_/D` | -0.019607 | -0.021732 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 6 | `dpath.a_reg.out[3]$_DFFE_PP_/D` | -0.01942 | -0.022508 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 7 | `dpath.a_reg.out[10]$_DFFE_PP_/D` | -0.019306 | None | 12 | 3 | 25047002.0 | slow_slew | NAND2_X1@_578_/ZN (slew 25047002.0), XNOR2_X2@_763_/ZN (slew 23333000.0) |
| 8 | `dpath.a_reg.out[2]$_DFFE_PP_/D` | -0.018564 | -0.021079 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 9 | `dpath.a_reg.out[0]$_DFFE_PP_/D` | -0.018145 | None | 14 | 5 | 28771000.0 | slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 10 | `dpath.a_reg.out[8]$_DFFE_PP_/D` | -0.017994 | -0.022223 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |

Tag histogram: slow_slew=38, io_constrained=18, high_fanout=13, near_zero=10

vs reference: improved 15, regressed 4, new in worst list 2, gone 2
- regressed `resp_msg[9]`: +0.0032 -> +0.0032
- regressed `resp_msg[8]`: +0.0212 -> +0.0043
- regressed `resp_msg[3]`: +0.0255 -> +0.0254
- regressed `resp_msg[2]`: +0.0617 -> +0.0610
- improved `dpath.a_reg.out[5]$_DFFE_PP_/D`: -0.0234 -> -0.0222
- improved `dpath.a_reg.out[4]$_DFFE_PP_/D`: -0.0226 -> -0.0219
- improved `dpath.a_reg.out[6]$_DFFE_PP_/D`: -0.0218 -> -0.0208
- improved `dpath.a_reg.out[12]$_DFFE_PP_/D`: -0.0213 -> -0.0177
- improved `dpath.a_reg.out[10]$_DFFE_PP_/D`: -0.0211 -> -0.0193

### nangate45/aes

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `sa10_sr[3]$_DFF_P_/D` | -0.024128 | None | 15 | 4 | 75224000.0 | slow_slew | OAI33_X1@_19597_/ZN (slew 75224000.0), XNOR2_X2@_14869_/ZN (slew 50566000.0) |
| 2 | `sa23_sr[0]$_DFF_P_/D` | -0.024078 | -0.064183 | 15 | 7 | 63210004.0 | slow_slew | OAI33_X1@_15856_/ZN (slew 63210004.0), XOR2_X2@_13050_/Z (slew 61395004.0) |
| 3 | `sa11_sr[3]$_DFF_P_/D` | -0.02377 | None | 14 | 5 | 53805004.0 | slow_slew | XOR2_X2@_16432_/Z (slew 53805004.0), AOI222_X2@_16838_/ZN (slew 46332004.0) |
| 4 | `sa23_sr[5]$_DFF_P_/D` | -0.023272 | -0.063612 | 16 | 7 | 61833004.0 | slow_slew | OAI33_X1@_16121_/ZN (slew 61833004.0), XOR2_X2@_13050_/Z (slew 61395004.0) |
| 5 | `sa23_sr[7]$_DFF_P_/D` | -0.023234 | None | 16 | 7 | 61395004.0 | slow_slew | XOR2_X2@_13050_/Z (slew 61395004.0), NOR2_X2@_13121_/ZN (slew 38508004.0) |
| 6 | `sa23_sr[4]$_DFF_P_/D` | -0.021825 | -0.067301 | 14 | 7 | 61395004.0 | slow_slew | XOR2_X2@_13050_/Z (slew 61395004.0), NOR2_X1@_13133_/ZN (slew 46299000.0) |
| 7 | `sa20_sr[7]$_DFF_P_/D` | -0.021035 | None | 15 | 6 | 50210000.0 | slow_slew | AOI222_X1@_14167_/ZN (slew 50210000.0), XNOR2_X2@_14128_/ZN (slew 48551004.0) |
| 8 | `sa01_sr[5]$_DFF_P_/D` | -0.020935 | None | 14 | 8 | 68560000.0 | high_fanout slow_slew | XOR2_X2@_12864_/Z (slew 68557000.0), OAI221_X1@_19328_/ZN (slew 38466000.0) |
| 9 | `sa03_sr[7]$_DFF_P_/D` | -0.020641 | None | 13 | 22 | 64911004.0 | high_fanout slow_slew | XOR2_X2@_13680_/Z (slew 64911004.0), AOI221_X1@_13791_/ZN (slew 44726000.0) |
| 10 | `sa33_sr[3]$_DFF_P_/D` | -0.020592 | None | 15 | 6 | 54957000.0 | slow_slew | XNOR2_X2@_11702_/ZN (slew 54956000.0), AOI221_X2@_14665_/ZN (slew 47715004.0) |

Tag histogram: slow_slew=40, io_constrained=20, high_fanout=6

vs reference: improved 13, regressed 1, new in worst list 3, gone 3
- regressed `sa10_sr[3]$_DFF_P_/D`: -0.0227 -> -0.0241
- improved `sa33_sr[3]$_DFF_P_/D`: -0.0258 -> -0.0206
- improved `sa11_sr[3]$_DFF_P_/D`: -0.0247 -> -0.0238
- improved `sa23_sr[0]$_DFF_P_/D`: -0.0242 -> -0.0241
- improved `sa23_sr[5]$_DFF_P_/D`: -0.0234 -> -0.0233
- improved `sa23_sr[7]$_DFF_P_/D`: -0.0233 -> -0.0232

### nangate45/ibex

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `gen_regfile_ff.register_file_i.rf_reg[982]$_DFFE_PN0P_/D` | -0.07424 | -0.192484 | 37 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), NOR3_X1@_20302_/ZN (slew 73603000.0) |
| 2 | `gen_regfile_ff.register_file_i.rf_reg[854]$_DFFE_PN0P_/D` | -0.073687 | -0.191003 | 37 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), NOR3_X1@_20302_/ZN (slew 73603000.0) |
| 3 | `gen_regfile_ff.register_file_i.rf_reg[662]$_DFFE_PN0P_/D` | -0.073604 | -0.190917 | 37 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), NOR3_X1@_20302_/ZN (slew 73603000.0) |
| 4 | `gen_regfile_ff.register_file_i.rf_reg[566]$_DFFE_PN0P_/D` | -0.073601 | -0.191195 | 37 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), NOR3_X1@_20302_/ZN (slew 73603000.0) |
| 5 | `gen_regfile_ff.register_file_i.rf_reg[694]$_DFFE_PN0P_/D` | -0.073511 | -0.190967 | 37 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), NOR3_X1@_20302_/ZN (slew 73603000.0) |
| 6 | `gen_regfile_ff.register_file_i.rf_reg[790]$_DFFE_PN0P_/D` | -0.073247 | -0.190903 | 37 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), NOR3_X1@_20302_/ZN (slew 73603000.0) |
| 7 | `gen_regfile_ff.register_file_i.rf_reg[918]$_DFFE_PN0P_/D` | -0.073211 | -0.190553 | 37 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), NOR3_X1@_20302_/ZN (slew 73603000.0) |
| 8 | `gen_regfile_ff.register_file_i.rf_reg[758]$_DFFE_PN0P_/D` | -0.073144 | -0.190743 | 37 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), NOR3_X1@_20302_/ZN (slew 73603000.0) |
| 9 | `gen_regfile_ff.register_file_i.rf_reg[703]$_DFFE_PN0P_/D` | -0.073038 | None | 33 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57553004.0) |
| 10 | `gen_regfile_ff.register_file_i.rf_reg[726]$_DFFE_PN0P_/D` | -0.073021 | -0.190621 | 37 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), NOR3_X1@_20302_/ZN (slew 73603000.0) |

Tag histogram: slow_slew=61, high_fanout=60, deep_logic=40, io_constrained=40, near_zero=8

vs reference: improved 15, regressed 13, new in worst list 13, gone 13
- regressed `instr_addr_o[30]`: -0.0522 -> -0.0587
- regressed `instr_addr_o[22]`: +0.0001 -> -0.0155
- regressed `instr_addr_o[23]`: +0.0106 -> +0.0033
- regressed `instr_addr_o[26]`: +0.0267 -> +0.0102
- regressed `instr_addr_o[27]`: +0.0217 -> +0.0155
- improved `gen_regfile_ff.register_file_i.rf_reg[703]$_DFFE_PN0P_/D`: -0.0794 -> -0.0730
- improved `gen_regfile_ff.register_file_i.rf_reg[607]$_DFFE_PN0P_/D`: -0.0790 -> -0.0726
- improved `gen_regfile_ff.register_file_i.rf_reg[831]$_DFFE_PN0P_/D`: -0.0788 -> -0.0724
- improved `gen_regfile_ff.register_file_i.rf_reg[799]$_DFFE_PN0P_/D`: -0.0788 -> -0.0724
- improved `gen_regfile_ff.register_file_i.rf_reg[982]$_DFFE_PN0P_/D`: -0.0784 -> -0.0742

### nangate45/jpeg

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `fdct_zigzag.dct_mod.dct_block_5.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.085302 | None | 22 | 15 | 36248000.0 | deep_logic high_fanout slow_slew | DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0), HA_X1@_114238_/S (slew 27197000.0) |
| 2 | `fdct_zigzag.dct_mod.dct_block_2.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.085137 | None | 19 | 12 | 28754000.0 | deep_logic high_fanout slow_slew | HA_X1@_115515_/S (slew 28754000.0), NOR3_X2@_106305_/ZN (slew 28456002.0) |
| 3 | `fdct_zigzag.dct_mod.dct_block_7.dct_unit_4.macu.mult_res[15]$_DFFE_PP_/D` | -0.084674 | None | 20 | 15 | 40669004.0 | deep_logic high_fanout slow_slew | HA_X1@_115122_/S (slew 40669004.0), DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0) |
| 4 | `fdct_zigzag.dct_mod.dct_block_7.dct_unit_2.macu.mult_res[18]$_DFFE_PP_/D` | -0.083894 | -0.111903 | 22 | 17 | 39042000.0 | deep_logic high_fanout slow_slew | FA_X1@_109354_/S (slew 39042000.0), HA_X1@_115805_/S (slew 37304000.0) |
| 5 | `fdct_zigzag.dct_mod.dct_block_5.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D` | -0.08352 | None | 21 | 15 | 39442000.0 | deep_logic high_fanout slow_slew | OAI221_X1@_095447_/ZN (slew 39442000.0), DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0) |
| 6 | `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.083447 | None | 20 | 12 | 28983002.0 | deep_logic high_fanout slow_slew | HA_X1@_115442_/S (slew 28983002.0), FA_X1@_108721_/S (slew 24679000.0) |
| 7 | `fdct_zigzag.dct_mod.dct_block_1.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D` | -0.083002 | None | 23 | 17 | 38575004.0 | deep_logic high_fanout slow_slew | HA_X1@_115070_/S (slew 38575004.0), AOI21_X1@_081689_/ZN (slew 34703004.0) |
| 8 | `fdct_zigzag.dct_mod.dct_block_3.dct_unit_3.macu.mult_res[16]$_DFFE_PP_/D` | -0.082844 | None | 23 | 17 | 35726000.0 | deep_logic high_fanout slow_slew | HA_X1@_115059_/S (slew 35726000.0), OAI21_X1@_089120_/ZN (slew 33784000.0) |
| 9 | `fdct_zigzag.dct_mod.dct_block_1.dct_unit_2.macu.mult_res[18]$_DFFE_PP_/D` | -0.082825 | None | 23 | 17 | 38575004.0 | deep_logic high_fanout slow_slew | HA_X1@_115070_/S (slew 38575004.0), AOI21_X1@_081689_/ZN (slew 34703004.0) |
| 10 | `fdct_zigzag.dct_mod.dct_block_6.dct_unit_2.macu.mult_res[17]$_DFFE_PP_/D` | -0.082652 | None | 19 | 34 | 49913000.0 | deep_logic high_fanout slow_slew | HA_X1@_112926_/S (slew 49913000.0), OAI221_X1@_100271_/ZN (slew 36012004.0) |

Tag histogram: slow_slew=60, high_fanout=40, io_constrained=40, deep_logic=20

vs reference: improved 5, regressed 4, new in worst list 6, gone 6
- regressed `fdct_zigzag.dct_mod.dct_block_2.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D`: -0.0843 -> -0.0851
- regressed `fdct_zigzag.dct_mod.dct_block_3.dct_unit_3.macu.mult_res[16]$_DFFE_PP_/D`: -0.0827 -> -0.0828
- regressed `fdct_zigzag.dct_mod.dct_block_2.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D`: -0.0825 -> -0.0826
- regressed `fdct_zigzag.dct_mod.dct_block_7.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D`: -0.0819 -> -0.0825
- improved `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D`: -0.0866 -> -0.0834
- improved `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D`: -0.0834 -> -0.0802
- improved `fdct_zigzag.dct_mod.dct_block_1.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D`: -0.0831 -> -0.0830
- improved `fdct_zigzag.dct_mod.dct_block_1.dct_unit_2.macu.mult_res[18]$_DFFE_PP_/D`: -0.0829 -> -0.0828
- improved `fdct_zigzag.dct_mod.dct_block_6.dct_unit_6.macu.mult_res[16]$_DFFE_PP_/D`: -0.0823 -> -0.0823

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
