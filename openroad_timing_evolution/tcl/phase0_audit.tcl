# Read-only timing/electrical audit for a post-CTS checkpoint.
read_liberty $::env(EVO_LIB)
read_db $::env(EVO_ODB)
read_sdc $::env(EVO_SDC)
source $::env(EVO_SET_RC)
estimate_parasitics -placement

report_wns -max
report_tns -max
report_wns -min
report_tns -min
report_check_types -max_slew -max_capacitance -max_fanout -violators
report_design_area

puts "PHASE0_AUDIT_PASS"
