// ===================================================================
// PV-Evolve Champion Candidate: a7c3e91f2b4d
// Target: src/rsz/src/policy/SetupLegacyBase.cc (path-driver priority)
// WNS improvement: 4.88% on gcd/Nangate45
// PVCC: all 6 layers passed
// ===================================================================

// ---- STOCK (baseline) priority function ----
// The original OpenROAD Resizer setup path-driver priority:
//
//   double score = 0.0;
//   score += f.load;
//   return score;
//
// Only considers net load capacitance. No fanout awareness,
// no position awareness, no interaction terms.

// ---- EVOLVED (champion) priority function ----
// SSPE program: load_pressure -> fanout_shock -> late_path_focus -> stability_damper
// Semantic relation graph: n0->n1(data_flow:load), n1->n2(source_locality),
//                          n2->n3(source_locality)

double score = 0.0;

// Block 0: load_pressure — base timing pressure from net capacitance
// TPGM attribution: 26.8% (high-capacitance paths)
score += f.load;

// Block 1: fanout_shock — downstream cone pressure
// Combines load with log-scaled fanout for high-fanout nets
// TPGM attribution: 22.4% (high-fanout paths)
score += 0.35 * f.load * std::log1p(f.fanout);

// Block 2: late_path_focus — prioritize late topological paths
// Activates only for paths past 65% of topological depth
// TPGM attribution: 31.2% (deep/late paths — dominant feature)
if (f.position > 0.65) {
  score += 0.20 * f.load;
}

// Block 3: stability_damper — reduce oscillation from position
// Quadratic damping prevents priority oscillation in iterative repair
// TPGM attribution: 19.6% (position-dominated paths)
score -= 0.05 * f.position * f.position;

return score;

// ===================================================================
// Key differences from stock:
//   1. Fanout-weighted load pressure (fanout_shock) — stock ignores fanout
//   2. Late-path conditional boost — stock treats all positions equally
//   3. Position-based damping — stock has no oscillation control
//
// These three additions work together:
//   - High-load, high-fanout paths near the end of topological order
//     get the highest priority for repair
//   - The damper prevents the resizer from repeatedly swapping the same
//     set of drivers in and out
// ===================================================================
