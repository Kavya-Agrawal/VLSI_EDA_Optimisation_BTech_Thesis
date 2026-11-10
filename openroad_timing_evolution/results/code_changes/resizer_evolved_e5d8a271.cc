// PV-Evolve Candidate: e5d8a271cc09
// Target: src/rsz/src/policy/SetupLegacyBase.cc
// WNS improvement: +2.85% on gcd/Nangate45
// PVCC: all 6 layers PASS
// SSPE program: load_pressure -> late_path_focus -> fanout_shock

double SetupLegacyBase::priorityScore(const DriverFeatures& f) const
{
  double score = 0.0;

  // Block 0: load_pressure
  score += f.load;

  // Block 1: late_path_focus
  if (f.position > 0.70) {
    score += 0.15 * f.load;
  }

  // Block 2: fanout_shock
  score += 0.22 * f.load * std::log1p(f.fanout);

  return score;
}
