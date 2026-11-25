# Candidate `champion_tierB_stressed`

tier B, variant `stressed`, replicates 2, evaluated 2026-11-25T15:37:07Z

## Verdict vs champion

```
REJECT  score=+0.00000
  ! nangate45/gcd: candidate evaluation failed (missing)
  ! nangate45/aes: candidate evaluation failed (missing)
  ! nangate45/ibex: candidate evaluation failed (missing)
  ! nangate45/jpeg: candidate evaluation failed (missing)
```

## Verdict vs baseline (stock OpenROAD)

```
ACCEPT  score=+0.00054
  asap7/ibex         WNS -100.9572 -> -100.1145 ns  TNS -78044.636 -> -77830.265 ns  score +0.00054
```

## Did the new logic run? (RSZ_EVOLVE counters per design)

- asap7/ibex: {'bottleneck_rounds': 5, 'bottleneck_drivers_ranked': 4669, 'bottleneck_trials': 290, 'bottleneck_kept': 13, 'bottleneck_rejected_wns': 19, 'bottleneck_rejected_tns': 21}  | moves {'buffers_inserted': 84, 'resized': 170, 'pins_swapped': 162, 'cloned': 28} vs baseline {'buffers_inserted': 83, 'resized': 172, 'pins_swapped': 159, 'cloned': 28}

## Worst paths after repair (candidate)

### asap7/ibex

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `gen_regfile_ff.register_file_i.rf_reg[765]$_DFFE_PN0P_/D` | -100.114471 | None | 43 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), FAx1_ASAP7_75t_R@_17071_/SN (slew 30979781558272.0) |
| 2 | `gen_regfile_ff.register_file_i.rf_reg[414]$_DFFE_PN0P_/D` | -100.083939 | None | 44 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), OAI22x1_ASAP7_75t_R@_22833_/Y (slew 74274882715648.0) |
| 3 | `gen_regfile_ff.register_file_i.rf_reg[446]$_DFFE_PN0P_/D` | -99.971924 | None | 44 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), OAI22x1_ASAP7_75t_R@_22833_/Y (slew 74274882715648.0) |
| 4 | `gen_regfile_ff.register_file_i.rf_reg[541]$_DFFE_PN0P_/D` | -99.938057 | None | 43 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), FAx1_ASAP7_75t_R@_17071_/SN (slew 30979781558272.0) |
| 5 | `gen_regfile_ff.register_file_i.rf_reg[638]$_DFFE_PN0P_/D` | -99.929176 | None | 44 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), OAI22x1_ASAP7_75t_R@_22833_/Y (slew 74274882715648.0) |
| 6 | `gen_regfile_ff.register_file_i.rf_reg[797]$_DFFE_PN0P_/D` | -99.919853 | None | 43 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), FAx1_ASAP7_75t_R@_17071_/SN (slew 30979781558272.0) |
| 7 | `gen_regfile_ff.register_file_i.rf_reg[158]$_DFFE_PN0P_/D` | -99.903084 | None | 44 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), OAI22x1_ASAP7_75t_R@_22833_/Y (slew 74274882715648.0) |
| 8 | `gen_regfile_ff.register_file_i.rf_reg[510]$_DFFE_PN0P_/D` | -99.871887 | None | 44 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), OAI22x1_ASAP7_75t_R@_22833_/Y (slew 74274882715648.0) |
| 9 | `gen_regfile_ff.register_file_i.rf_reg[701]$_DFFE_PN0P_/D` | -99.857346 | None | 43 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), FAx1_ASAP7_75t_R@_17071_/SN (slew 30979781558272.0) |
| 10 | `gen_regfile_ff.register_file_i.rf_reg[894]$_DFFE_PN0P_/D` | -99.838585 | None | 44 | 944 | 1438949469847552.0 | deep_logic high_fanout slow_slew | AND2x2_ASAP7_75t_R@_22158_/Y (slew 1438949469847552.0), OAI22x1_ASAP7_75t_R@_22833_/Y (slew 74274882715648.0) |

Tag histogram: slow_slew=61, high_fanout=60, deep_logic=40, io_constrained=40

vs reference: improved 5, regressed 15, new in worst list 6, gone 6
- regressed `gen_regfile_ff.register_file_i.rf_reg[539]$_DFFE_PN0P_/D`: -99.4759 -> -99.4763
- regressed `instr_addr_o[20]`: -62.1569 -> -66.8736
- regressed `instr_addr_o[16]`: -66.7618 -> -66.7988
- regressed `instr_addr_o[28]`: -56.0255 -> -60.7422
- regressed `instr_addr_o[19]`: -54.1274 -> -59.5159
- improved `gen_regfile_ff.register_file_i.rf_reg[638]$_DFFE_PN0P_/D`: -100.9572 -> -99.9292
- improved `gen_regfile_ff.register_file_i.rf_reg[894]$_DFFE_PN0P_/D`: -100.8666 -> -99.8386
- improved `gen_regfile_ff.register_file_i.rf_reg[574]$_DFFE_PN0P_/D`: -100.8433 -> -99.8153
- improved `gen_regfile_ff.register_file_i.rf_reg[862]$_DFFE_PN0P_/D`: -100.8400 -> -99.8120
- improved `gen_regfile_ff.register_file_i.rf_reg[830]$_DFFE_PN0P_/D`: -100.5980 -> -99.5699

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
