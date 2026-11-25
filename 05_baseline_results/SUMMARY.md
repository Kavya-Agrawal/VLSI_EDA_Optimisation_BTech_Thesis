# Baseline (stock OpenROAD)

binary: `/Users/kavyaagrawal/Desktop/Github repos and Projects/VLSI_EDA_Optimisation_BTech_Thesis/build/bin/openroad_stock`  commit: `6932b6296c65aebaadae64850f5a23265758ead0`  updated: 2026-11-25T12:26:08Z

repair_timing args: `-setup -repair_tns 100 -verbose`

## SDC variant: stressed

| design | period (ns) | endpoints | WNS pre | WNS post | TNS pre | TNS post | hold WNS | area um2 | buffers | repair ms | deterministic |
|---|---|---|---|---|---|---|---|---|---|---|---|
| nangate45/aes | 0.738 | 1248 | -0.0790 | -0.0258 | -8.116 | -1.141 | +0.1020 | 20555 | 3346 | 27546 | yes |
| nangate45/gcd | 0.375 | 72 | -0.0250 | -0.0234 | -0.732 | -0.475 | +0.0870 | 822 | 156 | 1630 | yes |
| nangate45/ibex | 1.98 | 5565 | -0.1925 | -0.0794 | -164.022 | -65.665 | +0.0447 | 28627 | 1091 | 41270 | yes |
| nangate45/jpeg | 1 | 8355 | -0.1165 | -0.0866 | -48.300 | -32.403 | +0.0084 | 90200 | 5571 | 35942 | yes |

### nangate45/aes (stressed) worst paths after stock repair

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `sa33_sr[3]$_DFF_P_/D` | -0.025841 | None | 15 | 6 | 54957000.0 | slow_slew | XNOR2_X2@_11702_/ZN (slew 54956000.0), AOI221_X2@_14665_/ZN (slew 47715004.0) |
| 2 | `sa11_sr[3]$_DFF_P_/D` | -0.024707 | None | 14 | 5 | 53805004.0 | slow_slew | XOR2_X2@_16432_/Z (slew 53805004.0), AOI222_X2@_16838_/ZN (slew 46332004.0) |
| 3 | `sa23_sr[0]$_DFF_P_/D` | -0.024186 | -0.064183 | 15 | 7 | 63210004.0 | slow_slew | OAI33_X1@_15856_/ZN (slew 63210004.0), XOR2_X2@_13050_/Z (slew 61395004.0) |
| 4 | `sa23_sr[5]$_DFF_P_/D` | -0.02338 | -0.063612 | 16 | 7 | 61833004.0 | slow_slew | OAI33_X1@_16121_/ZN (slew 61833004.0), XOR2_X2@_13050_/Z (slew 61395004.0) |
| 5 | `sa23_sr[7]$_DFF_P_/D` | -0.023341 | None | 16 | 7 | 61395004.0 | slow_slew | XOR2_X2@_13050_/Z (slew 61395004.0), NOR2_X2@_13121_/ZN (slew 38508004.0) |
| 6 | `sa01_sr[1]$_DFF_P_/D` | -0.023198 | None | 15 | 12 | 40925000.0 | high_fanout slow_slew | XNOR2_X1@_12865_/ZN (slew 40925000.0), BUF_X1@place6521/Z (slew 40578000.0) |
| 7 | `sa01_sr[5]$_DFF_P_/D` | -0.02308 | None | 15 | 12 | 40925000.0 | high_fanout slow_slew | XNOR2_X1@_12865_/ZN (slew 40925000.0), DFF_X1@sa31_sr[4]$_DFF_P_/Q (slew 39792004.0) |
| 8 | `sa10_sr[3]$_DFF_P_/D` | -0.022722 | None | 15 | 7 | 75224000.0 | slow_slew | OAI33_X1@_19597_/ZN (slew 75224000.0), XNOR2_X2@_14882_/ZN (slew 62456004.0) |

Tag histogram: slow_slew=40, io_constrained=20, high_fanout=8

### nangate45/gcd (stressed) worst paths after stock repair

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

Tag histogram: slow_slew=38, io_constrained=18, high_fanout=9, near_zero=5

### nangate45/ibex (stressed) worst paths after stock repair

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

Tag histogram: slow_slew=61, high_fanout=60, deep_logic=40, io_constrained=40, near_zero=8

### nangate45/jpeg (stressed) worst paths after stock repair

| # | endpoint | slack (ns) | pre-repair | stages | max fanout | worst slew | tags | worst drivers |
|---|---|---|---|---|---|---|---|---|
| 1 | `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.086623 | None | 20 | 12 | 28983002.0 | deep_logic high_fanout slow_slew | HA_X1@_115442_/S (slew 28983002.0), FA_X1@_108721_/S (slew 24679000.0) |
| 2 | `fdct_zigzag.dct_mod.dct_block_5.dct_unit_2.macu.mult_res[16]$_DFFE_PP_/D` | -0.085652 | None | 23 | 50 | 28272000.0 | deep_logic high_fanout slow_slew | HA_X1@_114387_/S (slew 28272000.0), OAI21_X1@_096477_/ZN (slew 26009002.0) |
| 3 | `fdct_zigzag.dct_mod.dct_block_5.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.085302 | None | 22 | 15 | 36248000.0 | deep_logic high_fanout slow_slew | DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0), HA_X1@_114238_/S (slew 27197000.0) |
| 4 | `fdct_zigzag.dct_mod.dct_block_7.dct_unit_4.macu.mult_res[15]$_DFFE_PP_/D` | -0.084674 | None | 20 | 15 | 40669004.0 | deep_logic high_fanout slow_slew | HA_X1@_115122_/S (slew 40669004.0), DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0) |
| 5 | `fdct_zigzag.dct_mod.dct_block_2.dct_unit_4.macu.mult_res[18]$_DFFE_PP_/D` | -0.084264 | None | 19 | 12 | 28754000.0 | deep_logic high_fanout slow_slew | HA_X1@_115515_/S (slew 28754000.0), NOR3_X2@_106305_/ZN (slew 28456002.0) |
| 6 | `fdct_zigzag.dct_mod.dct_block_6.dct_unit_7.macu.mult_res[16]$_DFFE_PP_/D` | -0.083542 | None | 22 | 50 | 34711000.0 | deep_logic high_fanout slow_slew | HA_X1@_115914_/S (slew 34711000.0), OAI21_X1@_097786_/ZN (slew 33434000.0) |
| 7 | `fdct_zigzag.dct_mod.dct_block_5.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D` | -0.08352 | None | 21 | 15 | 39442000.0 | deep_logic high_fanout slow_slew | OAI221_X1@_095447_/ZN (slew 39442000.0), DFFR_X2@fdct_zigzag.dct_mod.ddin[8]$_DFFE_PN0P_/Q (slew 36226000.0) |
| 8 | `fdct_zigzag.dct_mod.dct_block_6.dct_unit_4.macu.mult_res[17]$_DFFE_PP_/D` | -0.083396 | None | 23 | 12 | 36423004.0 | deep_logic high_fanout slow_slew | OAI221_X1@_099135_/ZN (slew 36423004.0), HA_X1@_114852_/S (slew 31154000.0) |

Tag histogram: slow_slew=60, high_fanout=40, io_constrained=40, deep_logic=20

