# Candidate `selftest_original`

tier A, variant `stressed`, replicates 1, evaluated 2026-11-12T21:33:10Z

## Verdict vs champion

```
REJECT  score=+0.00000
  nangate45/gcd      WNS -0.1742 -> -0.1742 ns  TNS -7.626 -> -7.626 ns  score +0.00000
  ! score +0.00000 below required gain +0.00200
```

## Verdict vs baseline (stock OpenROAD)

```
ACCEPT  score=+0.00000
  nangate45/gcd      WNS -0.1742 -> -0.1742 ns  TNS -7.626 -> -7.626 ns  score +0.00000
```

## Worst paths after repair (candidate)

### nangate45/gcd

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `dpath.a_reg.out[4]$_DFFE_PP_/D` | -0.174175 | -0.174712 | 16 | 8 | 21531002.0 | high_fanout slow_slew io_constrained | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 2 | `dpath.a_reg.out[12]$_DFFE_PP_/D` | -0.173529 | -0.172143 | 14 | 3 | 31418000.0 | slow_slew io_constrained | NOR2_X2@_950_/ZN (slew 31417002.0), INV_X1@_977_/ZN (slew 20363000.0) |
| 3 | `dpath.a_reg.out[5]$_DFFE_PP_/D` | -0.173366 | -0.173594 | 13 | 7 | 31418000.0 | slow_slew io_constrained | NOR2_X2@_950_/ZN (slew 31417002.0), INV_X1@_977_/ZN (slew 20363000.0) |
| 4 | `dpath.a_reg.out[6]$_DFFE_PP_/D` | -0.173335 | -0.173613 | 13 | 7 | 31418000.0 | slow_slew io_constrained | NOR2_X2@_950_/ZN (slew 31417002.0), INV_X1@_977_/ZN (slew 20363000.0) |
| 5 | `dpath.a_reg.out[10]$_DFFE_PP_/D` | -0.172897 | None | 13 | 4 | 23333000.0 | slow_slew io_constrained | XNOR2_X2@_763_/ZN (slew 23333000.0), DFF_X1@dpath.a_reg.out[4]$_DFFE_PP_/Q (slew 22566000.0) |
| 6 | `dpath.a_reg.out[9]$_DFFE_PP_/D` | -0.171188 | -0.172439 | 16 | 5 | 21531002.0 | slow_slew io_constrained | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 7 | `dpath.a_reg.out[8]$_DFFE_PP_/D` | -0.170942 | -0.172223 | 16 | 8 | 21531002.0 | high_fanout slow_slew io_constrained | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 8 | `dpath.a_reg.out[1]$_DFFE_PP_/D` | -0.170938 | -0.171732 | 13 | 7 | 31418000.0 | slow_slew io_constrained | NOR2_X2@_950_/ZN (slew 31417002.0), INV_X1@_977_/ZN (slew 20363000.0) |
| 9 | `dpath.a_reg.out[3]$_DFFE_PP_/D` | -0.1703 | -0.172508 | 16 | 8 | 21531002.0 | high_fanout slow_slew io_constrained | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 10 | `dpath.a_reg.out[2]$_DFFE_PP_/D` | -0.169929 | -0.171079 | 13 | 7 | 31418000.0 | slow_slew io_constrained | NOR2_X2@_950_/ZN (slew 31417002.0), INV_X1@_977_/ZN (slew 20363000.0) |

Tag histogram: slow_slew=38, io_constrained=38, high_fanout=7, near_zero=1

vs reference: improved 0, regressed 0, new in worst list 0, gone 0

## Build

20 s, 0 warnings
