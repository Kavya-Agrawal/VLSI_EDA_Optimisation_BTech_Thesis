// Stock OpenROAD Resizer: src/rsz/src/policy/SetupLegacyBase.cc
// Path-driver priority function (baseline)

double SetupLegacyBase::priorityScore(const DriverFeatures& f) const
{
  double score = 0.0;
  score += f.load;
  return score;
}
