# Replay the exact post-CTS setup-repair command emitted by the pinned ORFS
# scripts.  The surrounding load, parasitic estimate and legalization are
# trusted harness operations; only the policy ordering changes between runs.
read_liberty $::env(EVO_LIB)
read_db $::env(EVO_ODB)
read_sdc $::env(EVO_SDC)
source $::env(EVO_SET_RC)
estimate_parasitics -placement

set phase0_start_ms [clock milliseconds]
repair_timing -setup_margin 0 -hold_margin 0 -repair_tns 100 -verbose
set phase0_elapsed_ms [expr {[clock milliseconds] - $phase0_start_ms}]
puts "PHASE0_REPAIR_RUNTIME_MS $phase0_elapsed_ms"

detailed_placement
estimate_parasitics -placement
write_db $::env(EVO_OUT_ODB)
write_sdc -no_timestamp $::env(EVO_OUT_SDC)
puts "PHASE0_REPAIR_PASS"
