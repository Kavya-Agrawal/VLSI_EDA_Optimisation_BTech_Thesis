// PV-Evolve Candidate: b42f1e893a7c
// Target: src/rsz/src/policy/SetupLegacyBase.cc
// WNS improvement: +3.42% on gcd/Nangate45
// PVCC: all 6 layers PASS
// SSPE program: load_pressure -> fanout_shock -> stability_damper

double SetupLegacyBase::priorityScore(const DriverFeatures& f) const
{
  double score = 0.0;

  // Block 0: load_pressure
  score += f.load;

  // Block 1: fanout_shock
  score += 0.28 * f.load * std::log1p(f.fanout);

  // Block 2: stability_damper
  score -= 0.03 * f.position * f.position;

  return score;
}
