# Candidate `champion_tierA_nominal`

tier A, variant `nominal`, replicates 2, evaluated 2026-11-25T15:44:05Z

## Verdict vs champion

```
REJECT  score=+0.00107
  nangate45/gcd      WNS -0.1492 -> -0.1495 ns  TNS -6.327 -> -6.176 ns  score +0.00353
  nangate45/aes      WNS +0.0022 -> +0.0022 ns  TNS +0.000 -> +0.000 ns  score +0.00000
  nangate45/ibex     WNS +0.0264 -> +0.0264 ns  TNS +0.000 -> +0.000 ns  score +0.00000
  nangate45/jpeg     WNS -0.0866 -> -0.0853 ns  TNS -32.403 -> -31.151 ns  score +0.00074
  ! score +0.00107 below required gain +0.00200
```

## Verdict vs baseline (stock OpenROAD)

```
ACCEPT  score=+0.00107
  nangate45/gcd      WNS -0.1492 -> -0.1495 ns  TNS -6.327 -> -6.176 ns  score +0.00353
  nangate45/aes      WNS +0.0022 -> +0.0022 ns  TNS +0.000 -> +0.000 ns  score +0.00000
  nangate45/ibex     WNS +0.0264 -> +0.0264 ns  TNS +0.000 -> +0.000 ns  score +0.00000
  nangate45/jpeg     WNS -0.0866 -> -0.0853 ns  TNS -32.403 -> -31.151 ns  score +0.00074
```

## Did the new logic run? (RSZ_EVOLVE counters per design)

- nangate45/gcd: {'bottleneck_rounds': 5, 'bottleneck_drivers_ranked': 1234, 'bottleneck_trials': 340, 'bottleneck_kept': 24, 'bottleneck_rejected_wns': 43, 'bottleneck_rejected_tns': 51}  | moves {'resized': 73, 'pins_swapped': 1} vs baseline {'resized': 56, 'pins_swapped': 1}
- nangate45/aes: no counter lines  | moves {} vs baseline {}
- nangate45/ibex: no counter lines  | moves {} vs baseline {}
- nangate45/jpeg: {'bottleneck_rounds': 2, 'bottleneck_drivers_ranked': 8425, 'bottleneck_trials': 169, 'bottleneck_kept': 34, 'bottleneck_rejected_wns': 77, 'bottleneck_rejected_tns': 12}  | moves {'resized': 308, 'pins_swapped': 123, 'cloned': 1} vs baseline {'resized': 282, 'pins_swapped': 117}

## Worst paths after repair (candidate)

### nangate45/gcd

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `dpath.a_reg.out[4]$_DFFE_PP_/D` | -0.149517 | -0.149712 | 16 | 8 | 21531002.0 | high_fanout slow_slew | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 2 | `dpath.a_reg.out[5]$_DFFE_PP_/D` | -0.148133 | -0.148594 | 16 | 8 | 21531002.0 | high_fanout slow_slew | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 3 | `dpath.a_reg.out[6]$_DFFE_PP_/D` | -0.147168 | -0.148613 | 16 | 8 | 21531002.0 | high_fanout slow_slew | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 4 | `dpath.a_reg.out[9]$_DFFE_PP_/D` | -0.14653 | -0.147439 | 16 | 5 | 21531002.0 | slow_slew | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 5 | `dpath.a_reg.out[12]$_DFFE_PP_/D` | -0.14646 | -0.147143 | 15 | 3 | 28771000.0 | slow_slew | DFF_X1@dpath.a_reg.out[7]$_DFFE_PP_/Q (slew 28771000.0), OAI21_X2@_922_/ZN (slew 21385000.0) |
| 6 | `dpath.a_reg.out[8]$_DFFE_PP_/D` | -0.146284 | -0.147223 | 16 | 8 | 21531002.0 | high_fanout slow_slew | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 7 | `dpath.a_reg.out[1]$_DFFE_PP_/D` | -0.146236 | -0.146732 | 16 | 8 | 21531002.0 | high_fanout slow_slew | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 8 | `dpath.a_reg.out[3]$_DFFE_PP_/D` | -0.145642 | -0.147508 | 16 | 8 | 21531002.0 | high_fanout slow_slew | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 9 | `dpath.a_reg.out[2]$_DFFE_PP_/D` | -0.145167 | -0.146079 | 16 | 8 | 21531002.0 | high_fanout slow_slew | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 10 | `dpath.a_reg.out[7]$_DFFE_PP_/D` | -0.144888 | None | 16 | 8 | 21531002.0 | high_fanout slow_slew | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |

Tag histogram: slow_slew=38, io_constrained=18, high_fanout=12, near_zero=2

vs reference: improved 15, regressed 15, new in worst list 3, gone 3
- regressed `dpath.a_reg.out[4]$_DFFE_PP_/D`: -0.1492 -> -0.1495
- regressed `dpath.a_reg.out[9]$_DFFE_PP_/D`: -0.1462 -> -0.1465
- regressed `dpath.a_reg.out[8]$_DFFE_PP_/D`: -0.1459 -> -0.1463
- regressed `dpath.a_reg.out[1]$_DFFE_PP_/D`: -0.1459 -> -0.1462
- regressed `dpath.a_reg.out[3]$_DFFE_PP_/D`: -0.1453 -> -0.1456
- improved `dpath.a_reg.out[12]$_DFFE_PP_/D`: -0.1485 -> -0.1465
- improved `dpath.a_reg.out[5]$_DFFE_PP_/D`: -0.1484 -> -0.1481
- improved `dpath.a_reg.out[6]$_DFFE_PP_/D`: -0.1483 -> -0.1472
- improved `dpath.a_reg.out[10]$_DFFE_PP_/D`: -0.1479 -> -0.1440
- improved `dpath.a_reg.out[13]$_DFFE_PP_/D`: -0.1409 -> -0.1404

### nangate45/aes

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `sa31_sr[6]$_DFF_P_/D` | 0.002248 | 0.003017 | 16 | 15 | 90875000.0 | high_fanout slow_slew near_zero | XOR2_X2@_11995_/Z (slew 90869008.0), XNOR2_X1@_11992_/ZN (slew 59428000.0) |
| 2 | `sa31_sr[3]$_DFF_P_/D` | 0.004172 | 0.005074 | 14 | 15 | 90875000.0 | high_fanout slow_slew near_zero | XOR2_X2@_11995_/Z (slew 90869008.0), XNOR2_X1@_11992_/ZN (slew 59428000.0) |
| 3 | `sa31_sr[5]$_DFF_P_/D` | 0.008358 | 0.009445 | 15 | 15 | 90873008.0 | high_fanout slow_slew near_zero | XOR2_X2@_11995_/Z (slew 90869008.0), XNOR2_X1@_11992_/ZN (slew 59428000.0) |
| 4 | `u0.u3.d[3]$_DFF_P_/D` | 0.010006 | 0.012525 | 15 | 7 | 78933000.0 | slow_slew near_zero | XNOR2_X1@_21083_/ZN (slew 78917000.0), XNOR2_X1@_21055_/ZN (slew 65456004.0) |
| 5 | `sa31_sr[0]$_DFF_P_/D` | 0.011683 | 0.01221 | 15 | 15 | 90879000.0 | high_fanout slow_slew near_zero | XOR2_X2@_11995_/Z (slew 90869008.0), XNOR2_X1@_11992_/ZN (slew 59428000.0) |
| 6 | `sa23_sr[4]$_DFF_P_/D` | 0.011754 | 0.014699 | 13 | 16 | 50108004.0 | high_fanout slow_slew near_zero | XNOR2_X1@_13044_/ZN (slew 50108004.0), XNOR2_X1@_13066_/ZN (slew 45603000.0) |
| 7 | `u0.u3.d[0]$_DFF_P_/D` | 0.012124 | 0.013765 | 15 | 11 | 78933000.0 | high_fanout slow_slew near_zero | XNOR2_X1@_21083_/ZN (slew 78917000.0), XNOR2_X1@_21055_/ZN (slew 65456004.0) |
| 8 | `sa31_sr[4]$_DFF_P_/D` | 0.012952 | 0.014279 | 14 | 15 | 90870000.0 | high_fanout slow_slew near_zero | XOR2_X2@_11995_/Z (slew 90869008.0), NOR2_X1@_12045_/ZN (slew 66166000.0) |
| 9 | `sa23_sr[3]$_DFF_P_/D` | 0.013544 | 0.016606 | 14 | 11 | 50108004.0 | high_fanout slow_slew near_zero | XNOR2_X1@_13044_/ZN (slew 50108004.0), NAND2_X1@_13142_/ZN (slew 48704000.0) |
| 10 | `sa23_sr[5]$_DFF_P_/D` | 0.015007 | 0.018388 | 15 | 16 | 50108004.0 | high_fanout slow_slew near_zero | XNOR2_X1@_13044_/ZN (slew 50108004.0), NOR2_X1@_13089_/ZN (slew 46795000.0) |

Tag histogram: slow_slew=40, io_constrained=20, high_fanout=18, near_zero=14

vs reference: improved 0, regressed 0, new in worst list 0, gone 0

### nangate45/ibex

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `gen_regfile_ff.register_file_i.rf_reg[982]$_DFFE_PN0P_/D` | 0.0264 | 0.027516 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 2 | `gen_regfile_ff.register_file_i.rf_reg[854]$_DFFE_PN0P_/D` | 0.026951 | 0.028997 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 3 | `gen_regfile_ff.register_file_i.rf_reg[662]$_DFFE_PN0P_/D` | 0.027031 | 0.029083 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 4 | `gen_regfile_ff.register_file_i.rf_reg[566]$_DFFE_PN0P_/D` | 0.027037 | 0.028805 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 5 | `gen_regfile_ff.register_file_i.rf_reg[694]$_DFFE_PN0P_/D` | 0.027123 | 0.029033 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 6 | `gen_regfile_ff.register_file_i.rf_reg[790]$_DFFE_PN0P_/D` | 0.027389 | 0.029097 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 7 | `gen_regfile_ff.register_file_i.rf_reg[918]$_DFFE_PN0P_/D` | 0.027429 | 0.029447 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 8 | `gen_regfile_ff.register_file_i.rf_reg[758]$_DFFE_PN0P_/D` | 0.02749 | 0.029257 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 9 | `gen_regfile_ff.register_file_i.rf_reg[726]$_DFFE_PN0P_/D` | 0.027612 | 0.029379 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 10 | `gen_regfile_ff.register_file_i.rf_reg[950]$_DFFE_PN0P_/D` | 0.027621 | 0.029616 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |

Tag histogram: slow_slew=61, high_fanout=60, deep_logic=40, io_constrained=40, near_zero=20

vs reference: improved 0, regressed 0, new in worst list 0, gone 0

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
