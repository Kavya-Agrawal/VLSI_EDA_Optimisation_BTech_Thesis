# Candidate `0008_setup_strategy`

tier A, variant `stressed`, replicates 1, evaluated 2026-11-25T13:23:43Z

## Verdict vs champion

```
REJECT  score=+0.00063
  nangate45/gcd      WNS -0.0234 -> -0.0201 ns  TNS -0.475 -> -0.376 ns  score +0.00616
  nangate45/aes      WNS -0.0258 -> -0.0426 ns  TNS -1.141 -> -1.689 ns  score -0.01167
  nangate45/ibex     WNS -0.0794 -> -0.0605 ns  TNS -65.665 -> -8.111 ns  score +0.00739
  ! nangate45/jpeg: candidate evaluation failed (timeout)
  ! score +0.00063 below required gain +0.00200
  ! instrumentation missing: no RSZ_EVOLVE counter lines printed, cannot tell if the new logic ran
```

## Verdict vs baseline (stock OpenROAD)

```
REJECT  score=+0.00063
  nangate45/gcd      WNS -0.0234 -> -0.0201 ns  TNS -0.475 -> -0.376 ns  score +0.00616
  nangate45/aes      WNS -0.0258 -> -0.0426 ns  TNS -1.141 -> -1.689 ns  score -0.01167
  nangate45/ibex     WNS -0.0794 -> -0.0605 ns  TNS -65.665 -> -8.111 ns  score +0.00739
  ! nangate45/jpeg: candidate evaluation failed (timeout)
  ! instrumentation missing: no RSZ_EVOLVE counter lines printed, cannot tell if the new logic ran
```

## Did the new logic run? (RSZ_EVOLVE counters per design)

- nangate45/gcd: no counter lines  | moves {'resized': 34} vs baseline {'resized': 24, 'pins_swapped': 1}
- nangate45/aes: no counter lines  | moves {'buffers_inserted': 706, 'resized': 612, 'pins_swapped': 2, 'cloned': 13} vs baseline {'buffers_removed': 7, 'buffers_inserted': 481, 'resized': 1388, 'pins_swapped': 132, 'cloned': 70}
- nangate45/ibex: no counter lines  | moves {'buffers_inserted': 191, 'resized': 218, 'cloned': 9} vs baseline {'resized': 149, 'pins_swapped': 14, 'cloned': 9}

## Worst paths after repair (candidate)

### nangate45/gcd

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `dpath.a_reg.out[4]$_DFFE_PP_/D` | -0.020123 | -0.024712 | 14 | 8 | 25890000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[5]$_DFFE_PP_/Q (slew 25890000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 2 | `dpath.a_reg.out[12]$_DFFE_PP_/D` | -0.019669 | -0.022143 | 14 | 3 | 30365000.0 | slow_slew | NOR2_X2@_950_/ZN (slew 30365000.0), INV_X1@_977_/ZN (slew 20276002.0) |
| 3 | `dpath.a_reg.out[9]$_DFFE_PP_/D` | -0.017943 | -0.022439 | 14 | 5 | 25890000.0 | slow_slew | DFF_X1@dpath.a_reg.out[5]$_DFFE_PP_/Q (slew 25890000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 4 | `dpath.a_reg.out[1]$_DFFE_PP_/D` | -0.017827 | -0.021732 | 14 | 8 | 25890000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[5]$_DFFE_PP_/Q (slew 25890000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 5 | `dpath.a_reg.out[5]$_DFFE_PP_/D` | -0.017688 | -0.023594 | 14 | 8 | 25890000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[5]$_DFFE_PP_/Q (slew 25890000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 6 | `dpath.a_reg.out[3]$_DFFE_PP_/D` | -0.017632 | -0.022508 | 14 | 8 | 25890000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[5]$_DFFE_PP_/Q (slew 25890000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 7 | `dpath.a_reg.out[6]$_DFFE_PP_/D` | -0.017219 | -0.023613 | 14 | 8 | 25890000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[5]$_DFFE_PP_/Q (slew 25890000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 8 | `dpath.a_reg.out[2]$_DFFE_PP_/D` | -0.016784 | -0.021079 | 14 | 8 | 25890000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[5]$_DFFE_PP_/Q (slew 25890000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 9 | `dpath.a_reg.out[7]$_DFFE_PP_/D` | -0.016595 | None | 14 | 8 | 25890000.0 | high_fanout slow_slew | DFF_X1@dpath.a_reg.out[5]$_DFFE_PP_/Q (slew 25890000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |
| 10 | `dpath.a_reg.out[0]$_DFFE_PP_/D` | -0.016273 | None | 14 | 5 | 25890000.0 | slow_slew | DFF_X1@dpath.a_reg.out[5]$_DFFE_PP_/Q (slew 25890000.0), AOI21_X4@_604_/ZN (slew 21531002.0) |

Tag histogram: slow_slew=38, io_constrained=18, high_fanout=13, near_zero=12

vs reference: improved 15, regressed 8, new in worst list 0, gone 0
- regressed `dpath.a_reg.out[11]$_DFFE_PP_/D`: -0.0141 -> -0.0148
- regressed `resp_msg[14]`: -0.0119 -> -0.0130
- regressed `resp_msg[11]`: -0.0064 -> -0.0075
- regressed `resp_msg[8]`: +0.0212 -> -0.0001
- regressed `resp_msg[9]`: +0.0032 -> +0.0012
- improved `dpath.a_reg.out[5]$_DFFE_PP_/D`: -0.0234 -> -0.0177
- improved `dpath.a_reg.out[4]$_DFFE_PP_/D`: -0.0226 -> -0.0201
- improved `dpath.a_reg.out[6]$_DFFE_PP_/D`: -0.0218 -> -0.0172
- improved `dpath.a_reg.out[12]$_DFFE_PP_/D`: -0.0213 -> -0.0197
- improved `dpath.a_reg.out[10]$_DFFE_PP_/D`: -0.0211 -> -0.0151

### nangate45/aes

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `sa23_sr[0]$_DFF_P_/D` | -0.042631 | -0.064183 | 13 | 9 | 63514004.0 | high_fanout slow_slew | OAI33_X1@_15856_/ZN (slew 63514004.0), AOI221_X1@_15853_/ZN (slew 42285000.0) |
| 2 | `sa23_sr[5]$_DFF_P_/D` | -0.040305 | -0.063612 | 14 | 9 | 61875004.0 | high_fanout slow_slew | NOR2_X1@_13121_/ZN (slew 61875004.0), OAI33_X1@_16121_/ZN (slew 61830000.0) |
| 3 | `sa02_sr[2]$_DFF_P_/D` | -0.035177 | None | 15 | 8 | 55712000.0 | high_fanout slow_slew | XNOR2_X2@_13246_/ZN (slew 55706004.0), AOI221_X1@_20088_/ZN (slew 42176000.0) |
| 4 | `sa10_sr[2]$_DFF_P_/D` | -0.031225 | None | 14 | 15 | 42766004.0 | high_fanout slow_slew | NOR4_X1@_19577_/ZN (slew 42766004.0), OAI221_X1@_19571_/ZN (slew 39726000.0) |
| 5 | `sa33_sr[3]$_DFF_P_/D` | -0.02998 | None | 14 | 8 | 63820000.0 | high_fanout slow_slew | XOR2_X2@_11703_/Z (slew 63816004.0), XNOR2_X2@_11700_/ZN (slew 39275004.0) |
| 6 | `sa31_sr[0]$_DFF_P_/D` | -0.029551 | -0.06979 | 15 | 18 | 86374000.0 | high_fanout slow_slew | XNOR2_X2@_11977_/ZN (slew 86371000.0), OAI221_X1@_15509_/ZN (slew 35723000.0) |
| 7 | `sa21_sr[1]$_DFF_P_/D` | -0.029474 | None | 14 | 8 | 59834000.0 | high_fanout slow_slew | XOR2_X2@_18045_/Z (slew 59827000.0), AOI222_X2@_20702_/ZN (slew 43097000.0) |
| 8 | `sa21_sr[3]$_DFF_P_/D` | -0.029092 | None | 14 | 8 | 59832000.0 | high_fanout slow_slew | XOR2_X2@_18045_/Z (slew 59827000.0), AOI221_X1@_20780_/ZN (slew 42238000.0) |
| 9 | `sa00_sr[5]$_DFF_P_/D` | -0.028965 | None | 13 | 6 | 67124000.0 | slow_slew | NOR2_X1@_12387_/ZN (slew 67124000.0), XOR2_X2@_12346_/Z (slew 40746000.0) |
| 10 | `sa02_sr[7]$_DFF_P_/D` | -0.027419 | None | 16 | 8 | 59451000.0 | high_fanout slow_slew | XOR2_X2@_13247_/Z (slew 59451000.0), AOI221_X1@_13394_/ZN (slew 42551000.0) |

Tag histogram: slow_slew=40, io_constrained=20, high_fanout=16

vs reference: improved 0, regressed 7, new in worst list 13, gone 13
- regressed `sa23_sr[0]$_DFF_P_/D`: -0.0242 -> -0.0426
- regressed `sa23_sr[5]$_DFF_P_/D`: -0.0234 -> -0.0403
- regressed `sa33_sr[3]$_DFF_P_/D`: -0.0258 -> -0.0300
- regressed `sa02_sr[7]$_DFF_P_/D`: -0.0211 -> -0.0274
- regressed `sa10_sr[3]$_DFF_P_/D`: -0.0227 -> -0.0261

### nangate45/ibex

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `gen_regfile_ff.register_file_i.rf_reg[982]$_DFFE_PN0P_/D` | -0.060493 | -0.192484 | 42 | 943 | 2087884928.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087884928.0), NOR3_X1@_20302_/ZN (slew 73613008.0) |
| 2 | `gen_regfile_ff.register_file_i.rf_reg[854]$_DFFE_PN0P_/D` | -0.05994 | -0.191003 | 42 | 943 | 2087884928.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087884928.0), NOR3_X1@_20302_/ZN (slew 73613008.0) |
| 3 | `gen_regfile_ff.register_file_i.rf_reg[662]$_DFFE_PN0P_/D` | -0.059857 | -0.190917 | 42 | 943 | 2087884928.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087884928.0), NOR3_X1@_20302_/ZN (slew 73613008.0) |
| 4 | `gen_regfile_ff.register_file_i.rf_reg[566]$_DFFE_PN0P_/D` | -0.059855 | -0.191195 | 42 | 943 | 2087884928.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087884928.0), NOR3_X1@_20302_/ZN (slew 73613008.0) |
| 5 | `gen_regfile_ff.register_file_i.rf_reg[694]$_DFFE_PN0P_/D` | -0.059765 | -0.190967 | 42 | 943 | 2087884928.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087884928.0), NOR3_X1@_20302_/ZN (slew 73613008.0) |
| 6 | `gen_regfile_ff.register_file_i.rf_reg[790]$_DFFE_PN0P_/D` | -0.059501 | -0.190903 | 42 | 943 | 2087884928.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087884928.0), NOR3_X1@_20302_/ZN (slew 73613008.0) |
| 7 | `gen_regfile_ff.register_file_i.rf_reg[918]$_DFFE_PN0P_/D` | -0.059465 | -0.190553 | 42 | 943 | 2087884928.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087884928.0), NOR3_X1@_20302_/ZN (slew 73613008.0) |
| 8 | `gen_regfile_ff.register_file_i.rf_reg[758]$_DFFE_PN0P_/D` | -0.059398 | -0.190743 | 42 | 943 | 2087884928.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087884928.0), NOR3_X1@_20302_/ZN (slew 73613008.0) |
| 9 | `gen_regfile_ff.register_file_i.rf_reg[726]$_DFFE_PN0P_/D` | -0.059275 | -0.190621 | 42 | 943 | 2087884928.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087884928.0), NOR3_X1@_20302_/ZN (slew 73613008.0) |
| 10 | `gen_regfile_ff.register_file_i.rf_reg[950]$_DFFE_PN0P_/D` | -0.059272 | -0.190384 | 42 | 943 | 2087884928.0 | deep_logic high_fanout slow_slew | AND2_X1@_26153_/ZN (slew 2087884928.0), NOR3_X1@_20302_/ZN (slew 73613008.0) |

Tag histogram: slow_slew=61, high_fanout=60, io_constrained=40, deep_logic=39, near_zero=9

vs reference: improved 15, regressed 3, new in worst list 15, gone 15
- regressed `instr_addr_o[24]`: +0.0305 -> +0.0293
- regressed `instr_addr_o[25]`: +0.0931 -> +0.0891
- regressed `instr_addr_o[12]`: +0.1280 -> +0.1145
- improved `gen_regfile_ff.register_file_i.rf_reg[982]$_DFFE_PN0P_/D`: -0.0784 -> -0.0605
- improved `gen_regfile_ff.register_file_i.rf_reg[854]$_DFFE_PN0P_/D`: -0.0778 -> -0.0599
- improved `gen_regfile_ff.register_file_i.rf_reg[662]$_DFFE_PN0P_/D`: -0.0777 -> -0.0599
- improved `instr_addr_o[31]`: -0.0573 -> -0.0046
- improved `instr_addr_o[30]`: -0.0522 -> -0.0071

### nangate45/jpeg

FAILED: timeout

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
