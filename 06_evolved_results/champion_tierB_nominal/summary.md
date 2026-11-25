# Candidate `champion_tierB_nominal`

tier B, variant `nominal`, replicates 2, evaluated 2026-11-25T15:39:24Z

## Verdict vs champion

```
REJECT  score=+0.00000
  asap7/ibex         WNS -10.9572 -> -10.9587 ns  TNS -1163.875 -> -1109.557 ns  score +0.00000
  ! score +0.00000 below required gain +0.00200
```

## Verdict vs baseline (stock OpenROAD)

```
ACCEPT  score=+0.00000
  asap7/ibex         WNS -10.9572 -> -10.9587 ns  TNS -1163.875 -> -1109.557 ns  score +0.00000
```

## Did the new logic run? (RSZ_EVOLVE counters per design)

- asap7/ibex: {'bottleneck_rounds': 4, 'bottleneck_drivers_ranked': 2545, 'bottleneck_trials': 226, 'bottleneck_kept': 8, 'bottleneck_rejected_wns': 7, 'bottleneck_rejected_tns': 19}  | moves {'buffers_inserted': 84, 'resized': 161, 'pins_swapped': 149, 'cloned': 28} vs baseline {'buffers_inserted': 83, 'resized': 160, 'pins_swapped': 153, 'cloned': 28}

## Worst paths after repair (candidate)

### asap7/ibex

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `gen_regfile_ff.register_file_i.rf_reg[638]$_DFFE_PN0P_/D` | -10.958678 | None | 44 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew near_zero | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), OAI22x1_ASAP7_75t_R@_22833_/Y (slew 74274882715648.0) |
| 2 | `gen_regfile_ff.register_file_i.rf_reg[894]$_DFFE_PN0P_/D` | -10.868084 | None | 44 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew near_zero | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), OAI22x1_ASAP7_75t_R@_22833_/Y (slew 74274882715648.0) |
| 3 | `gen_regfile_ff.register_file_i.rf_reg[574]$_DFFE_PN0P_/D` | -10.844769 | None | 44 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew near_zero | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), OAI22x1_ASAP7_75t_R@_22833_/Y (slew 74274882715648.0) |
| 4 | `gen_regfile_ff.register_file_i.rf_reg[862]$_DFFE_PN0P_/D` | -10.841439 | None | 44 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew near_zero | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), OAI22x1_ASAP7_75t_R@_22833_/Y (slew 74274882715648.0) |
| 5 | `gen_regfile_ff.register_file_i.rf_reg[830]$_DFFE_PN0P_/D` | -10.59941 | None | 44 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew near_zero | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), OAI22x1_ASAP7_75t_R@_22833_/Y (slew 74274882715648.0) |
| 6 | `gen_regfile_ff.register_file_i.rf_reg[765]$_DFFE_PN0P_/D` | -10.114465 | None | 43 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew near_zero | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), FAx1_ASAP7_75t_R@_17071_/SN (slew 30979781558272.0) |
| 7 | `gen_regfile_ff.register_file_i.rf_reg[541]$_DFFE_PN0P_/D` | -9.93805 | None | 43 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew near_zero | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), FAx1_ASAP7_75t_R@_17071_/SN (slew 30979781558272.0) |
| 8 | `gen_regfile_ff.register_file_i.rf_reg[797]$_DFFE_PN0P_/D` | -9.919843 | None | 43 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew near_zero | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), FAx1_ASAP7_75t_R@_17071_/SN (slew 30979781558272.0) |
| 9 | `gen_regfile_ff.register_file_i.rf_reg[701]$_DFFE_PN0P_/D` | -9.857337 | None | 43 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew near_zero | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), FAx1_ASAP7_75t_R@_17071_/SN (slew 30979781558272.0) |
| 10 | `gen_regfile_ff.register_file_i.rf_reg[925]$_DFFE_PN0P_/D` | -9.670598 | None | 43 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew near_zero | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), FAx1_ASAP7_75t_R@_17071_/SN (slew 30979781558272.0) |

Tag histogram: slow_slew=61, high_fanout=60, deep_logic=40, io_constrained=40, near_zero=21

vs reference: improved 15, regressed 12, new in worst list 3, gone 3
- regressed `gen_regfile_ff.register_file_i.rf_reg[638]$_DFFE_PN0P_/D`: -10.9572 -> -10.9587
- regressed `gen_regfile_ff.register_file_i.rf_reg[894]$_DFFE_PN0P_/D`: -10.8666 -> -10.8681
- regressed `gen_regfile_ff.register_file_i.rf_reg[574]$_DFFE_PN0P_/D`: -10.8433 -> -10.8448
- regressed `gen_regfile_ff.register_file_i.rf_reg[862]$_DFFE_PN0P_/D`: -10.8400 -> -10.8414
- regressed `gen_regfile_ff.register_file_i.rf_reg[830]$_DFFE_PN0P_/D`: -10.5980 -> -10.5994
- improved `instr_addr_o[20]`: +21.4938 -> +21.7183
- improved `instr_addr_o[26]`: +24.1442 -> +29.8503
- improved `instr_addr_o[31]`: +25.9774 -> +28.2191
- improved `instr_addr_o[27]`: +26.8676 -> +31.2536
- improved `instr_addr_o[28]`: +27.6252 -> +27.8497

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
