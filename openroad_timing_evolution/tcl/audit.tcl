# Independent final-design audit: always run with the frozen stock binary.
# All paths are supplied by the trusted runner, never by an evolved policy.
read_liberty $::env(EVO_LIB)
read_db $::env(EVO_ODB)
read_sdc $::env(EVO_SDC)
set_cmd_units -time ns -capacitance pF -resistance kohm -distance um
read_spef $::env(EVO_SPEF)
set_propagated_clock [all_clocks]
if { [llength [all_clocks]] != 1 } {
  error "Current Nangate45 adapter requires exactly one constrained clock"
}
if { ![check_setup -no_clock -unconstrained_endpoints -loops -generated_clocks] } {
  error "Timing constraints are incomplete or contain loops"
}
check_placement -verbose
check_antennas
report_worst_negative_slack_metric
report_worst_negative_slack_metric -hold
report_tns_metric
report_tns_metric -hold
report_erc_metrics
report_clock_skew_metric
report_clock_skew_metric -hold
report_design_area_metrics
set clock [lindex [all_clocks] 0]
utl::metric_float "evo__period_ns" [sta::time_sta_ui [$clock period]]
utl::metric_int "evo__endpoints" [llength [sta::endpoints]]
utl::metric_int "evo__constraints_pass" 1
puts "RSZ_EVOLVE_AUDIT_PASS"
