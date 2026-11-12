# Baseline (stock OpenROAD)

binary: `/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/build/bin/openroad_stock`  commit: `6932b6296c65aebaadae64850f5a23265758ead0`  updated: 2026-11-12T22:04:42Z

repair_timing args: `-setup -repair_tns 100 -verbose`

## SDC variant: stressed

| design | period (ns) | endpoints | WNS pre | WNS post | TNS pre | TNS post | hold WNS | area um2 | buffers | repair ms | deterministic |
|---|---|---|---|---|---|---|---|---|---|---|---|
| nangate45/aes | 0.656 | 1248 | -0.1610 | -0.1083 | -21.236 | -14.773 | +0.1020 | 20272 | 3220 | 20776 | yes |
| nangate45/gcd | 0.225 | 72 | -0.1750 | -0.1742 | -8.003 | -7.626 | +0.0870 | 849 | 158 | 2311 | yes |
| nangate45/ibex | 1.76 | 5565 | -0.4125 | -0.2994 | -519.038 | -416.273 | +0.0447 | 28629 | 1091 | 45709 | yes |

### nangate45/aes (stressed) worst paths after stock repair

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `sa02_sr[2]$_DFF_P_/D` | -0.108289 | None | 18 | 7 | 43573000.0 | deep_logic slow_slew io_constrained | AOI221_X1@_20052_/ZN (slew 43573000.0), XOR2_X1@_13242_/Z (slew 27635002.0) |
| 2 | `sa02_sr[1]$_DFF_P_/D` | -0.108207 | -0.145662 | 16 | 12 | 54468000.0 | high_fanout slow_slew io_constrained | AOI221_X1@_20035_/ZN (slew 54468000.0), AOI221_X1@_19991_/ZN (slew 43744004.0) |
| 3 | `sa33_sr[3]$_DFF_P_/D` | -0.107356 | None | 15 | 6 | 54957000.0 | slow_slew io_constrained | XNOR2_X2@_11702_/ZN (slew 54956000.0), AOI221_X2@_14665_/ZN (slew 47715004.0) |
| 4 | `sa22_sr[3]$_DFF_P_/D` | -0.107087 | None | 16 | 5 | 43444000.0 | slow_slew io_constrained | OAI22_X1@_12676_/ZN (slew 43444000.0), AOI221_X2@_12681_/ZN (slew 40561004.0) |
| 5 | `sa23_sr[7]$_DFF_P_/D` | -0.105271 | None | 16 | 7 | 61395004.0 | slow_slew io_constrained | XOR2_X2@_13050_/Z (slew 61395004.0), NOR2_X2@_13121_/ZN (slew 38508004.0) |
| 6 | `sa23_sr[0]$_DFF_P_/D` | -0.105239 | -0.146183 | 16 | 7 | 63210004.0 | slow_slew io_constrained | OAI33_X1@_15856_/ZN (slew 63210004.0), XOR2_X2@_13050_/Z (slew 61395004.0) |
| 7 | `sa23_sr[5]$_DFF_P_/D` | -0.105222 | -0.145612 | 16 | 7 | 61830000.0 | slow_slew io_constrained | OAI33_X1@_16121_/ZN (slew 61830000.0), XOR2_X2@_13050_/Z (slew 61395004.0) |
| 8 | `sa22_sr[5]$_DFF_P_/D` | -0.105003 | None | 15 | 5 | 40273000.0 | slow_slew io_constrained | AOI221_X2@_12775_/ZN (slew 40273000.0), DFF_X1@sa30_sr[4]$_DFF_P_/Q (slew 37115000.0) |

Tag histogram: slow_slew=40, io_constrained=40, high_fanout=10, deep_logic=2

### nangate45/gcd (stressed) worst paths after stock repair

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

Tag histogram: slow_slew=38, io_constrained=38, high_fanout=7, near_zero=1

### nangate45/ibex (stressed) worst paths after stock repair

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `gen_regfile_ff.register_file_i.rf_reg[703]$_DFFE_PN0P_/D` | -0.299412 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew io_constrained | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 2 | `gen_regfile_ff.register_file_i.rf_reg[607]$_DFFE_PN0P_/D` | -0.299021 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew io_constrained | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 3 | `gen_regfile_ff.register_file_i.rf_reg[831]$_DFFE_PN0P_/D` | -0.298793 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew io_constrained | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 4 | `gen_regfile_ff.register_file_i.rf_reg[799]$_DFFE_PN0P_/D` | -0.298775 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew io_constrained | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 5 | `gen_regfile_ff.register_file_i.rf_reg[895]$_DFFE_PN0P_/D` | -0.29872 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew io_constrained | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 6 | `gen_regfile_ff.register_file_i.rf_reg[191]$_DFFE_PN0P_/D` | -0.298714 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew io_constrained | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 7 | `gen_regfile_ff.register_file_i.rf_reg[671]$_DFFE_PN0P_/D` | -0.298676 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew io_constrained | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |
| 8 | `gen_regfile_ff.register_file_i.rf_reg[735]$_DFFE_PN0P_/D` | -0.298558 | None | 35 | 943 | 2087753088.0 | deep_logic high_fanout slow_slew io_constrained | AND2_X1@_26153_/ZN (slew 2087753088.0), AOI221_X2@_22445_/ZN (slew 57608004.0) |

Tag histogram: slow_slew=61, io_constrained=61, high_fanout=60, deep_logic=40

## SDC variant: nominal

| design | period (ns) | endpoints | WNS pre | WNS post | TNS pre | TNS post | hold WNS | area um2 | buffers | repair ms | deterministic |
|---|---|---|---|---|---|---|---|---|---|---|---|
| nangate45/aes | 0.82 | 1248 | +0.0030 | +0.0022 | +0.000 | +0.000 | +0.1020 | 18802 | 2839 | 213 | yes |
| nangate45/gcd | 0.25 | 72 | -0.1500 | -0.1492 | -6.680 | -6.327 | +0.0870 | 845 | 157 | 2709 | yes |
| nangate45/ibex | 2.2 | 5565 | +0.0275 | +0.0264 | +0.000 | +0.000 | +0.0447 | 28364 | 1020 | 160 | yes |

### nangate45/aes (nominal) worst paths after stock repair

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `sa31_sr[6]$_DFF_P_/D` | 0.002248 | 0.003017 | 16 | 15 | 90875000.0 | high_fanout slow_slew io_constrained near_zero | XOR2_X2@_11995_/Z (slew 90869008.0), XNOR2_X1@_11992_/ZN (slew 59428000.0) |
| 2 | `sa31_sr[3]$_DFF_P_/D` | 0.004172 | 0.005074 | 14 | 15 | 90875000.0 | high_fanout slow_slew io_constrained near_zero | XOR2_X2@_11995_/Z (slew 90869008.0), XNOR2_X1@_11992_/ZN (slew 59428000.0) |
| 3 | `sa31_sr[5]$_DFF_P_/D` | 0.008358 | 0.009445 | 15 | 15 | 90873008.0 | high_fanout slow_slew io_constrained near_zero | XOR2_X2@_11995_/Z (slew 90869008.0), XNOR2_X1@_11992_/ZN (slew 59428000.0) |
| 4 | `u0.u3.d[3]$_DFF_P_/D` | 0.010006 | 0.012525 | 15 | 7 | 78933000.0 | slow_slew io_constrained near_zero | XNOR2_X1@_21083_/ZN (slew 78917000.0), XNOR2_X1@_21055_/ZN (slew 65456004.0) |
| 5 | `sa31_sr[0]$_DFF_P_/D` | 0.011683 | 0.01221 | 15 | 15 | 90879000.0 | high_fanout slow_slew io_constrained near_zero | XOR2_X2@_11995_/Z (slew 90869008.0), XNOR2_X1@_11992_/ZN (slew 59428000.0) |
| 6 | `sa23_sr[4]$_DFF_P_/D` | 0.011754 | 0.014699 | 13 | 16 | 50108004.0 | high_fanout slow_slew io_constrained near_zero | XNOR2_X1@_13044_/ZN (slew 50108004.0), XNOR2_X1@_13066_/ZN (slew 45603000.0) |
| 7 | `u0.u3.d[0]$_DFF_P_/D` | 0.012124 | 0.013765 | 15 | 11 | 78933000.0 | high_fanout slow_slew io_constrained near_zero | XNOR2_X1@_21083_/ZN (slew 78917000.0), XNOR2_X1@_21055_/ZN (slew 65456004.0) |
| 8 | `sa31_sr[4]$_DFF_P_/D` | 0.012952 | 0.014279 | 14 | 15 | 90870000.0 | high_fanout slow_slew io_constrained near_zero | XOR2_X2@_11995_/Z (slew 90869008.0), NOR2_X1@_12045_/ZN (slew 66166000.0) |

Tag histogram: slow_slew=40, io_constrained=40, high_fanout=18, near_zero=14

### nangate45/gcd (nominal) worst paths after stock repair

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `dpath.a_reg.out[4]$_DFFE_PP_/D` | -0.149175 | -0.149712 | 16 | 8 | 21531002.0 | high_fanout slow_slew io_constrained | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 2 | `dpath.a_reg.out[12]$_DFFE_PP_/D` | -0.148529 | -0.147143 | 14 | 3 | 31418000.0 | slow_slew io_constrained | NOR2_X2@_950_/ZN (slew 31417002.0), INV_X1@_977_/ZN (slew 20363000.0) |
| 3 | `dpath.a_reg.out[5]$_DFFE_PP_/D` | -0.148366 | -0.148594 | 13 | 7 | 31418000.0 | slow_slew io_constrained | NOR2_X2@_950_/ZN (slew 31417002.0), INV_X1@_977_/ZN (slew 20363000.0) |
| 4 | `dpath.a_reg.out[6]$_DFFE_PP_/D` | -0.148335 | -0.148613 | 13 | 7 | 31418000.0 | slow_slew io_constrained | NOR2_X2@_950_/ZN (slew 31417002.0), INV_X1@_977_/ZN (slew 20363000.0) |
| 5 | `dpath.a_reg.out[10]$_DFFE_PP_/D` | -0.147897 | None | 13 | 4 | 23333000.0 | slow_slew io_constrained | XNOR2_X2@_763_/ZN (slew 23333000.0), DFF_X1@dpath.a_reg.out[4]$_DFFE_PP_/Q (slew 22566000.0) |
| 6 | `dpath.a_reg.out[9]$_DFFE_PP_/D` | -0.146188 | -0.147439 | 16 | 5 | 21531002.0 | slow_slew io_constrained | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 7 | `dpath.a_reg.out[8]$_DFFE_PP_/D` | -0.145942 | -0.147223 | 16 | 8 | 21531002.0 | high_fanout slow_slew io_constrained | AOI21_X4@_604_/ZN (slew 21531002.0), DFF_X1@dpath.a_reg.out[3]$_DFFE_PP_/Q (slew 18275000.0) |
| 8 | `dpath.a_reg.out[1]$_DFFE_PP_/D` | -0.145938 | -0.146732 | 13 | 7 | 31418000.0 | slow_slew io_constrained | NOR2_X2@_950_/ZN (slew 31417002.0), INV_X1@_977_/ZN (slew 20363000.0) |

Tag histogram: slow_slew=38, io_constrained=38, high_fanout=8, near_zero=2

### nangate45/ibex (nominal) worst paths after stock repair

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `gen_regfile_ff.register_file_i.rf_reg[982]$_DFFE_PN0P_/D` | 0.0264 | 0.027516 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew io_constrained near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 2 | `gen_regfile_ff.register_file_i.rf_reg[854]$_DFFE_PN0P_/D` | 0.026951 | 0.028997 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew io_constrained near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 3 | `gen_regfile_ff.register_file_i.rf_reg[662]$_DFFE_PN0P_/D` | 0.027031 | 0.029083 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew io_constrained near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 4 | `gen_regfile_ff.register_file_i.rf_reg[566]$_DFFE_PN0P_/D` | 0.027037 | 0.028805 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew io_constrained near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 5 | `gen_regfile_ff.register_file_i.rf_reg[694]$_DFFE_PN0P_/D` | 0.027123 | 0.029033 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew io_constrained near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 6 | `gen_regfile_ff.register_file_i.rf_reg[790]$_DFFE_PN0P_/D` | 0.027389 | 0.029097 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew io_constrained near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 7 | `gen_regfile_ff.register_file_i.rf_reg[918]$_DFFE_PN0P_/D` | 0.027429 | 0.029447 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew io_constrained near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |
| 8 | `gen_regfile_ff.register_file_i.rf_reg[758]$_DFFE_PN0P_/D` | 0.02749 | 0.029257 | 41 | 943 | 2087928064.0 | deep_logic high_fanout slow_slew io_constrained near_zero | AND2_X1@_26153_/ZN (slew 2087928064.0), AOI221_X2@_19754_/ZN (slew 65262000.0) |

Tag histogram: slow_slew=61, io_constrained=61, high_fanout=60, deep_logic=40, near_zero=20

