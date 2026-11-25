# Candidate `0011_buffering`

tier A, variant `stressed`, replicates 1, evaluated 2026-11-25T13:51:53Z

## Verdict vs champion

```
REJECT  score=-0.00004
  nangate45/gcd      WNS -0.0234 -> -0.0234 ns  TNS -0.475 -> -0.475 ns  score +0.00000
  nangate45/aes      WNS -0.0258 -> -0.0259 ns  TNS -1.141 -> -1.292 ns  score -0.00015
  nangate45/ibex     WNS -0.0794 -> -0.0794 ns  TNS -65.665 -> -65.665 ns  score +0.00000
  nangate45/jpeg     WNS -0.0866 -> -0.0866 ns  TNS -32.403 -> -32.356 ns  score -0.00000
  ! score -0.00004 below required gain +0.00200
  ! instrumentation missing: no RSZ_EVOLVE counter lines printed, cannot tell if the new logic ran
```

## Verdict vs baseline (stock OpenROAD)

```
ACCEPT  score=-0.00004
  nangate45/gcd      WNS -0.0234 -> -0.0234 ns  TNS -0.475 -> -0.475 ns  score +0.00000
  nangate45/aes      WNS -0.0258 -> -0.0259 ns  TNS -1.141 -> -1.292 ns  score -0.00015
  nangate45/ibex     WNS -0.0794 -> -0.0794 ns  TNS -65.665 -> -65.665 ns  score +0.00000
  nangate45/jpeg     WNS -0.0866 -> -0.0866 ns  TNS -32.403 -> -32.356 ns  score -0.00000
  ! instrumentation missing: no RSZ_EVOLVE counter lines printed, cannot tell if the new logic ran
```

## Did the new logic run? (RSZ_EVOLVE counters per design)

- nangate45/gcd: no counter lines  | moves {'resized': 24, 'pins_swapped': 1} vs baseline {'resized': 24, 'pins_swapped': 1}
- nangate45/aes: no counter lines  | moves {'buffers_removed': 8, 'buffers_inserted': 398, 'resized': 1198, 'pins_swapped': 123, 'cloned': 54} vs baseline {'buffers_removed': 7, 'buffers_inserted': 481, 'resized': 1388, 'pins_swapped': 132, 'cloned': 70}
- nangate45/ibex: no counter lines  | moves {'resized': 149, 'pins_swapped': 13, 'cloned': 9} vs baseline {'resized': 149, 'pins_swapped': 14, 'cloned': 9}
- nangate45/jpeg: no counter lines  | moves {'resized': 262, 'pins_swapped': 103} vs baseline {'resized': 282, 'pins_swapped': 117}

## Worst paths after repair (candidate)

### nangate45/gcd

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `dpath.a_reg.out[5]$_DFFE_PP_/D` | -0.023366 | -0.023594 | 13 | 7 | 31418000.0 | slow_slew | NOR2_X2@_950_/ZN (slew 31417002.0), INV_X1@_977_/ZN (slew 20363000.0) |
| 2 | `dpath.a_reg.out[4]$_DFFE_PP_/D` | -0.022595 | -0.024712 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 3 | `dpath.a_reg.out[6]$_DFFE_PP_/D` | -0.021815 | -0.023613 | 13 | 7 | 31418000.0 | slow_slew | NOR2_X2@_950_/ZN (slew 31417002.0), INV_X1@_977_/ZN (slew 20363000.0) |
| 4 | `dpath.a_reg.out[12]$_DFFE_PP_/D` | -0.02127 | -0.022143 | 14 | 3 | 31418000.0 | slow_slew | NOR2_X2@_950_/ZN (slew 31417002.0), INV_X1@_977_/ZN (slew 20363000.0) |
| 5 | `dpath.a_reg.out[10]$_DFFE_PP_/D` | -0.021125 | None | 12 | 3 | 25047002.0 | slow_slew | NAND2_X1@_578_/ZN (slew 25047002.0), XNOR2_X2@_763_/ZN (slew 23333000.0) |
| 6 | `dpath.a_reg.out[1]$_DFFE_PP_/D` | -0.020938 | -0.021732 | 13 | 7 | 31418000.0 | slow_slew | NOR2_X2@_950_/ZN (slew 31417002.0), INV_X1@_977_/ZN (slew 20363000.0) |
| 7 | `dpath.a_reg.out[9]$_DFFE_PP_/D` | -0.020429 | -0.022439 | 14 | 5 | 28771000.0 | slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 8 | `dpath.a_reg.out[2]$_DFFE_PP_/D` | -0.019929 | -0.021079 | 13 | 7 | 31418000.0 | slow_slew | NOR2_X2@_950_/ZN (slew 31417002.0), INV_X1@_977_/ZN (slew 20363000.0) |
| 9 | `dpath.a_reg.out[3]$_DFFE_PP_/D` | -0.019826 | -0.022508 | 14 | 8 | 28771000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 10 | `dpath.a_reg.out[7]$_DFFE_PP_/D` | -0.019821 | None | 13 | 4 | 30345002.0 | slow_slew | XOR2_X2@_710_/Z (slew 30345002.0), DFF_X1@dpath.a_reg.out[5]$_DFFE_PP_/Q (slew 24936000.0) |

Tag histogram: slow_slew=38, io_constrained=18, high_fanout=9, near_zero=5

vs reference: improved 0, regressed 0, new in worst list 0, gone 0

### nangate45/aes

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `sa23_sr[0]$_DFF_P_/D` | -0.025939 | -0.064183 | 16 | 7 | 63210004.0 | slow_slew | OAI33_X1@_15856_/ZN (slew 63210004.0), XOR2_X2@_13050_/Z (slew 61395004.0) |
| 2 | `sa02_sr[2]$_DFF_P_/D` | -0.025284 | None | 18 | 7 | 43573000.0 | deep_logic slow_slew | AOI221_X1@_20052_/ZN (slew 43573000.0), AOI21_X1@_20051_/ZN (slew 26099000.0) |
| 3 | `sa20_sr[3]$_DFF_P_/D` | -0.024665 | -0.065526 | 15 | 8 | 65536000.0 | high_fanout slow_slew | OAI33_X1@_18423_/ZN (slew 65536000.0), NOR2_X1@_18327_/ZN (slew 37765000.0) |
| 4 | `sa23_sr[4]$_DFF_P_/D` | -0.024098 | -0.067301 | 16 | 7 | 61395004.0 | slow_slew | XOR2_X2@_13050_/Z (slew 61395004.0), OAI221_X1@_16090_/ZN (slew 35694000.0) |
| 5 | `sa20_sr[7]$_DFF_P_/D` | -0.02357 | None | 15 | 5 | 58913000.0 | slow_slew | XOR2_X2@_14139_/Z (slew 58913000.0), AOI221_X1@_14180_/ZN (slew 47290004.0) |
| 6 | `sa23_sr[5]$_DFF_P_/D` | -0.023374 | -0.063612 | 16 | 7 | 61833004.0 | slow_slew | OAI33_X1@_16121_/ZN (slew 61833004.0), XOR2_X2@_13050_/Z (slew 61395004.0) |
| 7 | `sa23_sr[7]$_DFF_P_/D` | -0.023337 | None | 16 | 7 | 61395004.0 | slow_slew | XOR2_X2@_13050_/Z (slew 61395004.0), NOR2_X2@_13121_/ZN (slew 38508004.0) |
| 8 | `sa33_sr[3]$_DFF_P_/D` | -0.022759 | None | 15 | 7 | 55729004.0 | slow_slew | XNOR2_X2@_11708_/ZN (slew 55725004.0), DFF_X1@sa12_sr[0]$_DFF_P_/Q (slew 41007004.0) |
| 9 | `sa01_sr[1]$_DFF_P_/D` | -0.022668 | None | 15 | 8 | 68560000.0 | high_fanout slow_slew | XOR2_X2@_12864_/Z (slew 68557000.0), NOR2_X1@_12916_/ZN (slew 67343000.0) |
| 10 | `sa11_sr[3]$_DFF_P_/D` | -0.022625 | None | 14 | 6 | 61129000.0 | slow_slew | XOR2_X2@_16092_/Z (slew 61129000.0), AOI222_X2@_16838_/ZN (slew 46330004.0) |

Tag histogram: slow_slew=40, io_constrained=20, high_fanout=5, deep_logic=1

vs reference: improved 8, regressed 5, new in worst list 7, gone 7
- regressed `sa23_sr[0]$_DFF_P_/D`: -0.0242 -> -0.0259
- regressed `sa23_sr[4]$_DFF_P_/D`: -0.0219 -> -0.0241
- regressed `sa20_sr[7]$_DFF_P_/D`: -0.0227 -> -0.0236
- regressed `sa02_sr[7]$_DFF_P_/D`: -0.0211 -> -0.0220
- regressed `sa11_sr[6]$_DFF_P_/D`: -0.0190 -> -0.0205
- improved `sa33_sr[3]$_DFF_P_/D`: -0.0258 -> -0.0228
- improved `sa11_sr[3]$_DFF_P_/D`: -0.0247 -> -0.0226
- improved `sa23_sr[5]$_DFF_P_/D`: -0.0234 -> -0.0234
- improved `sa23_sr[7]$_DFF_P_/D`: -0.0233 -> -0.0233
- improved `sa01_sr[1]$_DFF_P_/D`: -0.0232 -> -0.0227

### nangate45/ibex

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `gen_regfile_ff.register_file_i.rf_reg[703]$_DFFE_PN0P_/D` | -0.079412 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 2 | `gen_regfile_ff.register_file_i.rf_reg[607]$_DFFE_PN0P_/D` | -0.079021 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 3 | `gen_regfile_ff.register_file_i.rf_reg[831]$_DFFE_PN0P_/D` | -0.078793 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 4 | `gen_regfile_ff.register_file_i.rf_reg[799]$_DFFE_PN0P_/D` | -0.078775 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 5 | `gen_regfile_ff.register_file_i.rf_reg[895]$_DFFE_PN0P_/D` | -0.07872 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 6 | `gen_regfile_ff.register_file_i.rf_reg[191]$_DFFE_PN0P_/D` | -0.078714 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 7 | `gen_regfile_ff.register_file_i.rf_reg[671]$_DFFE_PN0P_/D` | -0.078676 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 8 | `gen_regfile_ff.register_file_i.rf_reg[735]$_DFFE_PN0P_/D` | -0.078558 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 9 | `gen_regfile_ff.register_file_i.rf_reg[63]$_DFFE_PN0P_/D` | -0.07854 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 10 | `gen_regfile_ff.register_file_i.rf_reg[927]$_DFFE_PN0P_/D` | -0.078431 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |

Tag histogram: slow_slew=61, high_fanout=60, deep_logic=40, io_constrained=40, near_zero=8

vs reference: improved 0, regressed 0, new in worst list 0, gone 0

### nangate45/jpeg

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.086631 | None | 20 | 12 | 28983002.0 | deep_logic high_fanout slow_slew | HA_X1@_115442_/S (slew 28983002.0), FA_X1@_108721_/S (slew 24679000.0) |
| 2 | `fdct_zigzag.dct_mod.dct_block_5.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D` | -0.08565 | None | 23 | 50 | 28272000.0 | deep_logic high_fanout slow_slew | HA_X1@_114387_/S (slew 28272000.0), OAI21_X1@_096477_/ZN (slew 26009002.0) |
| 3 | `fdct_zigzag.dct_mod.dct_block_5.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.085302 | None | 22 | 15 | 36248000.0 | deep_logic high_fanout slow_slew | DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0), HA_X1@_114238_/S (slew 27197000.0) |
| 4 | `fdct_zigzag.dct_mod.dct_block_7.dct_unit_4.macu.mult_res[15]$_DFFE_PP_/D` | -0.084674 | None | 20 | 15 | 40669004.0 | deep_logic high_fanout slow_slew | HA_X1@_115122_/S (slew 40669004.0), DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0) |
| 5 | `fdct_zigzag.dct_mod.dct_block_2.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.08428 | None | 19 | 12 | 28754000.0 | deep_logic high_fanout slow_slew | HA_X1@_115515_/S (slew 28754000.0), NOR3_X2@_106305_/ZN (slew 28456002.0) |
| 6 | `fdct_zigzag.dct_mod.dct_block_6.dct_unit_7.macu.mult_res[16]$_DFFE_PP_/D` | -0.08355 | None | 22 | 50 | 34711000.0 | deep_logic high_fanout slow_slew | HA_X1@_115914_/S (slew 34711000.0), OAI21_X1@_097786_/ZN (slew 33434000.0) |
| 7 | `fdct_zigzag.dct_mod.dct_block_5.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D` | -0.08352 | None | 21 | 15 | 39442000.0 | deep_logic high_fanout slow_slew | OAI221_X1@_095447_/ZN (slew 39442000.0), DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0) |
| 8 | `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D` | -0.083403 | None | 23 | 12 | 36423004.0 | deep_logic high_fanout slow_slew | OAI221_X1@_099135_/ZN (slew 36423004.0), HA_X1@_114852_/S (slew 31154000.0) |
| 9 | `fdct_zigzag.dct_mod.dct_block_1.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D` | -0.083073 | None | 23 | 17 | 38575004.0 | deep_logic high_fanout slow_slew | HA_X1@_115070_/S (slew 38575004.0), AOI21_X1@_081689_/ZN (slew 34703004.0) |
| 10 | `fdct_zigzag.dct_mod.dct_block_7.dct_unit_5.macu.mult_res[17]$_DFFE_PP_/D` | -0.083051 | None | 22 | 50 | 38933004.0 | deep_logic high_fanout slow_slew | OAI221_X1@_102373_/ZN (slew 38933004.0), FA_X1@_108274_/S (slew 38768000.0) |

Tag histogram: slow_slew=60, high_fanout=40, io_constrained=40, deep_logic=20

vs reference: improved 4, regressed 5, new in worst list 2, gone 2
- regressed `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D`: -0.0866 -> -0.0866
- regressed `fdct_zigzag.dct_mod.dct_block_2.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D`: -0.0843 -> -0.0843
- regressed `fdct_zigzag.dct_mod.dct_block_6.dct_unit_7.macu.mult_res[16]$_DFFE_PP_/D`: -0.0835 -> -0.0835
- regressed `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D`: -0.0834 -> -0.0834
- regressed `fdct_zigzag.dct_mod.dct_block_6.dct_unit_7.macu.mult_res[18]$_DFFE_PP_/D`: -0.0829 -> -0.0829
- improved `fdct_zigzag.dct_mod.dct_block_5.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D`: -0.0857 -> -0.0857
- improved `fdct_zigzag.dct_mod.dct_block_6.dct_unit_6.macu.mult_res[16]$_DFFE_PP_/D`: -0.0823 -> -0.0814
- improved `fdct_zigzag.dct_mod.dct_block_7.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D`: -0.0819 -> -0.0813
- improved `fdct_zigzag.dct_mod.dct_block_1.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D`: -0.0818 -> -0.0817

## Gates

```
gates: PASS
  unit  PASSED   //src/rsz/test:TestSkewBudget
  unit  PASSED   //src/rsz/test:TestInsertBuffer
  unit  PASSED   //src/rsz/test:TestNestedJournal
  unit  PASSED   //src/rsz/test:TestPreChecks
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
