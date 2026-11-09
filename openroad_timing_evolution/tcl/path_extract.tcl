# Timing-Path-Guided Mutation: extract top-K critical paths for attribution.
# Run AFTER audit.tcl in the same OpenSTA session.  Output is machine-parseable JSON.
# The trusted runner supplies EVO_PATH_OUT; the evolved policy never touches it.

set K 20
set out_path $::env(EVO_PATH_OUT)

set paths [find_timing_paths -sort_by_slack -path_delay max -max_paths $K]

set fd [open $out_path w]
puts $fd "\["
set first 1

foreach path $paths {
  set slack [sta::format_time [sta::path_slack $path] 4]
  set arrival [sta::format_time [sta::path_arrival $path] 4]
  set endpoint [get_full_name [sta::path_endpoint $path]]

  set pins {}
  set nets {}
  set max_cap 0.0
  set max_fanout 0
  set total_load 0.0
  set cell_count 0

  set pin_iter [$path pin_iterator]
  while {[$pin_iter has_next]} {
    set pin [$pin_iter next]
    set pin_name [get_full_name $pin]
    lappend pins $pin_name

    if {[sta::pin_is_driver $pin]} {
      set net [sta::pin_net $pin]
      if {$net != "NULL"} {
        set net_name [get_full_name $net]
        lappend nets $net_name
        set cap [sta::net_wire_cap $net max]
        set fo [llength [sta::net_load_pins $net]]
        set total_load [expr {$total_load + $cap}]
        if {$cap > $max_cap} { set max_cap $cap }
        if {$fo > $max_fanout} { set max_fanout $fo }
      }
      incr cell_count
    }
  }

  if {!$first} { puts $fd "," }
  set first 0
  puts $fd "  \{"
  puts $fd "    \"endpoint\": \"$endpoint\","
  puts $fd "    \"slack_ns\": $slack,"
  puts $fd "    \"arrival_ns\": $arrival,"
  puts $fd "    \"cell_count\": $cell_count,"
  puts $fd "    \"max_cap_pf\": $max_cap,"
  puts $fd "    \"max_fanout\": $max_fanout,"
  puts $fd "    \"total_load_pf\": $total_load,"
  puts $fd "    \"pin_count\": [llength $pins]"
  puts $fd "  \}"
}

puts $fd "\]"
close $fd
puts "RSZ_EVOLVE_PATH_EXTRACT_DONE paths=$K"
