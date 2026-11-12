# Evaluation contract (what every candidate is judged on)

<!-- generated from rszevolve/context/prompts/eval_contract.md; add '<!-- hand-edited -->' to freeze -->

**Input per benchmark**: a placed checkpoint produced by ORFS up to detailed placement with
`ENABLE_PLACE_REPAIR_TIMING=0` (so `repair_design` has run, `repair_timing` has not), the design SDC
(`stressed` variant = clock period tightened until stock repair leaves clear negative slack), platform
layer RC, dont_use list. Ideal clocks (pre-CTS).

**Commands run** (`rszevolve/eval/tcl/eval_repair_timing.tcl`, same as ORFS does at CTS time):
```
read_liberty ...; read_db placed.odb; read_sdc stressed.sdc; source setRC.tcl; set_dont_use ...
estimate_parasitics -placement
<pre metrics + worst paths>
repair_timing -setup -repair_tns 100 -verbose
detailed_placement ; check_placement
estimate_parasitics -placement
<post metrics + worst paths + report_checks + DRV report>
```

**Measured** (post-repair unless stated): setup WNS / TNS, setup endpoint violation count, hold WNS / TNS,
max slew / cap / fanout violation counts, instance count, buffer count, area, utilization, placement violations,
repair runtime, the N worst setup paths (endpoint, startpoint, slack, stages, max fanout, worst slew, per-pin cells).

**Score vs reference (champion)**, paired per design then averaged over the tier:
`0.5 * dWNS/period + 0.5 * dTNS/(period * endpoints)` (positive = better).

**Accepted only if all hold**: build ok; rsz C++ unit tests pass; smoke Tcl tests run without error; every design
evaluates; results identical across replicates; hold WNS not worse than reference by > tolerance; DRV count not
above reference + tolerance; placement legal; area growth within tolerance; score >= min_score_gain.

**Not measured, not rewarded**: runtime (only a timeout), code size, style.
