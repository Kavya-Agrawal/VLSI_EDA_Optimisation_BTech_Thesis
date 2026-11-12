# path_report.tcl — dump the N worst setup paths as JSON for the evaluator / planner agents.
# Sourced by eval_repair_timing.tcl; provides:  evo_write_paths <file> <count>
#
# Per path: endpoint, startpoint, slack, arrival, required, clock skew, number of pins/stages,
# worst slew on the path, max fanout of any net on the path, per-pin list (pin, cell, slew, fanout).
# Only OpenSTA public Tcl objects are used (PathEnd: pin/slack/path/data_arrival_time/
# data_required_time/clk_skew ; Path: pins) plus get_property.

proc evo_json_str { s } {
  set s [string map {\\ \\\\ \" \\\" \n \\n} $s]
  return "\"$s\""
}

proc evo_net_fanout { pin } {
  set nets [get_nets -quiet -of_objects $pin]
  if { [llength $nets] == 0 } { return 0 }
  set net [lindex $nets 0]
  set loads [get_pins -quiet -of_objects $net -filter "direction == input"]
  return [llength $loads]
}

proc evo_write_paths { filename count } {
  set ends [find_timing_paths -path_delay max -sort_by_slack -group_path_count $count]
  set f [open $filename w]
  puts $f "\["
  set first 1
  foreach pe $ends {
    set slack [$pe slack]
    set endpin [$pe pin]
    set endname [get_full_name $endpin]
    set path [$pe path]
    set pins [$path pins]
    # OpenSTA returns pins endpoint-first; present them startpoint-first
    if { [llength $pins] > 0 && [get_full_name [lindex $pins 0]] eq $endname } { set pins [lreverse $pins] }
    set startname ""
    if { [llength $pins] > 0 } { set startname [get_full_name [lindex $pins 0]] }
    # convert internal seconds to the user time unit (ns) like the reports do
    set slack [sta::format_time $slack 6]
    set arrival [sta::format_time [$pe data_arrival_time] 6]
    set required [sta::format_time [$pe data_required_time] 6]
    set skew 0
    catch { set skew [sta::format_time [$pe clk_skew] 6] }
    set worst_slew 0.0
    set max_fanout 0
    set stages 0
    set pin_entries {}
    foreach p $pins {
      set pname [get_full_name $p]
      set slew 0.0
      catch { set slew [sta::format_time [get_property $p slew_max] 6] }
      if { $slew > $worst_slew } { set worst_slew $slew }
      set cell ""
      set insts [get_cells -quiet -of_objects $p]
      if { [llength $insts] > 0 } { catch { set cell [get_property [lindex $insts 0] ref_name] } }
      set dir ""
      catch { set dir [get_property $p direction] }
      set fo 0
      if { $dir eq "output" } {
        set fo [evo_net_fanout $p]
        if { $fo > $max_fanout } { set max_fanout $fo }
        incr stages
      }
      lappend pin_entries "\{\"pin\": [evo_json_str $pname], \"cell\": [evo_json_str $cell], \"dir\": [evo_json_str $dir], \"slew\": $slew, \"fanout\": $fo\}"
    }
    if { !$first } { puts $f "," }
    set first 0
    puts $f "\{"
    puts $f "  \"endpoint\": [evo_json_str $endname],"
    puts $f "  \"startpoint\": [evo_json_str $startname],"
    puts $f "  \"slack\": $slack,"
    puts $f "  \"arrival\": $arrival,"
    puts $f "  \"required\": $required,"
    puts $f "  \"clk_skew\": $skew,"
    puts $f "  \"stages\": $stages,"
    puts $f "  \"pin_count\": [llength $pins],"
    puts $f "  \"worst_slew\": $worst_slew,"
    puts $f "  \"max_fanout\": $max_fanout,"
    puts $f "  \"pins\": \[[join $pin_entries ", "]\]"
    puts -nonewline $f "\}"
  }
  puts $f ""
  puts $f "\]"
  close $f
  puts "EVO_PATHS wrote [llength $ends] paths to $filename"
}
