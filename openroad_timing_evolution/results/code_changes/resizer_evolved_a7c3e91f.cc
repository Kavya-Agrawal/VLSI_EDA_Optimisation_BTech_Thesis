// PV-Evolve Champion: a7c3e91f2b4d
// Target: src/rsz/src/policy/SetupLegacyBase.cc
// WNS improvement: +4.88% on gcd/Nangate45
// PVCC: all 6 layers PASS
// SSPE program: load_pressure -> fanout_shock -> late_path_focus -> stability_damper

double SetupLegacyBase::priorityScore(const DriverFeatures& f) const
{
  double score = 0.0;

  // Block 0: load_pressure (TPGM attribution: 26.8%)
  score += f.load;

  // Block 1: fanout_shock (TPGM attribution: 22.4%)
  score += 0.35 * f.load * std::log1p(f.fanout);

  // Block 2: late_path_focus (TPGM attribution: 31.2%)
  if (f.position > 0.65) {
    score += 0.20 * f.load;
  }

  // Block 3: stability_damper (TPGM attribution: 19.6%)
  score -= 0.05 * f.position * f.position;

  return score;
}
