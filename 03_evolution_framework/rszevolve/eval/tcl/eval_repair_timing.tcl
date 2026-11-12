# eval_repair_timing.tcl — the fast pre-route evaluation loop for one design.
#
# Mirrors what OpenROAD-flow-scripts does the first time it calls repair_timing on a placed design,
# without CTS, routing or GDS:  load placed checkpoint -> placement parasitics -> repair_timing ->
# re-legalize -> placement parasitics -> report.  Everything measurable is written as JSON.
#
# Inputs (environment variables, all required unless noted):
#   EVO_LIBS         semicolon-separated liberty files (paths may contain spaces)
#   EVO_ODB          placed checkpoint (post detailed placement, pre-CTS)  (or EVO_LEFS + EVO_DEF)
#   EVO_SDC          constraints
#   EVO_SET_RC       platform setRC.tcl (set_layer_rc / set_wire_rc)
#   EVO_OUT_DIR      directory for metrics.json, paths.json, post.odb (optional write)
#   EVO_REPAIR_ARGS  arguments for repair_timing (default: -setup -repair_tns 100 -verbose)
#   EVO_PATH_COUNT   worst paths to dump (default 20)
#   EVO_DONT_USE     optional dont_use cell list
#   EVO_WRITE_ODB    1 to also write post-repair ODB (default 0)
#   EVO_SKIP_REPAIR  1 to only measure (used for pre-repair baselines / calibration)
#
# Run:  openroad -exit -no_splash -metrics $EVO_OUT_DIR/or_metrics.json eval_repair_timing.tcl

proc evo_env { name {default ""} } {
  if { [info exists ::env($name)] && $::env($name) ne "" } { return $::env($name) }
  return $default
}

set out_dir [evo_env EVO_OUT_DIR "."]
file mkdir $out_dir
set path_count [evo_env EVO_PATH_COUNT 20]
set repair_args [evo_env EVO_REPAIR_ARGS "-setup -repair_tns 100 -verbose"]
set skip_repair [evo_env EVO_SKIP_REPAIR 0]

# ---------------------------------------------------------------- load
foreach lib [split [evo_env EVO_LIBS] ";"] { if { $lib ne "" } { read_liberty $lib } }
if { [evo_env EVO_ODB] ne "" } {
  read_db [evo_env EVO_ODB]
} else {
  # DEF input (used by smoke tests with the rsz regression designs)
  foreach lef [split [evo_env EVO_LEFS] ";"] { if { $lef ne "" } { read_lef $lef } }
  read_def [evo_env EVO_DEF]
}
read_sdc [evo_env EVO_SDC]
source [evo_env EVO_SET_RC]
set dont_use [evo_env EVO_DONT_USE]
if { $dont_use ne "" } { set_dont_use $dont_use }

source [file join [file dirname [info script]] path_report.tcl]

# ---------------------------------------------------------------- helpers
proc evo_metrics { tag } {
  # returns a dict of the numbers we care about at this moment
  set d [dict create]
  dict set d wns_setup [worst_slack -max]
  dict set d tns_setup [total_negative_slack -max]
  dict set d wns_hold  [worst_slack -min]
  dict set d tns_hold  [total_negative_slack -min]
  dict set d setup_violations [sta::endpoint_violation_count max]
  dict set d hold_violations  [sta::endpoint_violation_count min]
  dict set d instances [sta::network_leaf_instance_count]
  dict set d pins      [sta::network_leaf_pin_count]
  dict set d area_um2  [expr {[rsz::design_area] * 1e12}]
  dict set d util      [rsz::utilization]
  set buf 0
  foreach inst [get_cells -hier *] {
    set cell [get_property $inst ref_name]
    if { [string match "BUF_*" $cell] || [string match "CLKBUF_*" $cell] || [string match "BUFx*" $cell] || [string match "HB*" $cell] } { incr buf }
  }
  dict set d buffers $buf
  # DRV counts
  set slew [sta::max_slew_violation_count]
  set cap  [sta::max_capacitance_violation_count]
  set fo   [sta::max_fanout_violation_count]
  dict set d drv_slew $slew
  dict set d drv_cap $cap
  dict set d drv_fanout $fo
  puts "EVO_METRICS $tag [dict get $d wns_setup] [dict get $d tns_setup] [dict get $d wns_hold] [dict get $d tns_hold] inst=[dict get $d instances] area=[dict get $d area_um2] buf=$buf drv=$slew/$cap/$fo"
  return $d
}

proc evo_dict_to_json { d } {
  set parts {}
  dict for {k v} $d {
    if { [string is double -strict $v] } { lappend parts "\"$k\": $v" } else { lappend parts "\"$k\": \"$v\"" }
  }
  return "\{[join $parts ", "]\}"
}

# ---------------------------------------------------------------- pre-repair
set clk_period 0
foreach clk [all_clocks] {
  set p [get_property $clk period]
  if { $p > $clk_period } { set clk_period $p }
}
set endpoints [sta::endpoint_count]

estimate_parasitics -placement
set pre [evo_metrics pre]
evo_write_paths "$out_dir/paths_pre.json" $path_count

# ---------------------------------------------------------------- repair
set t0 [clock milliseconds]
set repair_log ""
if { !$skip_repair } {
  puts "EVO_REPAIR_CMD repair_timing $repair_args"
  repair_timing {*}$repair_args
  # legalize whatever the resizer moved / inserted, then re-estimate (as ORFS does)
  detailed_placement
  set viol [check_placement]
  if { $viol eq "" } { set viol 0 }
  puts "EVO_PLACEMENT_VIOLATIONS $viol"
  estimate_parasitics -placement
}
set repair_ms [expr {[clock milliseconds] - $t0}]

# ---------------------------------------------------------------- post-repair
set post [evo_metrics post]
evo_write_paths "$out_dir/paths_post.json" $path_count
report_checks -path_delay max -group_count 5 -fields {slew cap input net fanout} -digits 3 -format full_clock_expanded > "$out_dir/report_checks_post.txt"
report_check_types -max_slew -max_capacitance -max_fanout -violators > "$out_dir/report_drv_post.txt"
if { [evo_env EVO_WRITE_ODB 0] } { write_db "$out_dir/post.odb" }

# ---------------------------------------------------------------- metrics.json
set f [open "$out_dir/metrics.json" w]
puts $f "\{"
puts $f "  \"clock_period_ns\": $clk_period,"
puts $f "  \"endpoints\": $endpoints,"
puts $f "  \"repair_args\": \"$repair_args\","
puts $f "  \"repair_ms\": $repair_ms,"
puts $f "  \"placement_violations\": [expr {[info exists viol] && $viol ne "" ? $viol : -1}],"
puts $f "  \"pre\": [evo_dict_to_json $pre],"
puts $f "  \"post\": [evo_dict_to_json $post]"
puts $f "\}"
close $f
puts "EVO_DONE wns_pre=[dict get $pre wns_setup] wns_post=[dict get $post wns_setup] tns_pre=[dict get $pre tns_setup] tns_post=[dict get $post tns_setup] repair_ms=$repair_ms"
