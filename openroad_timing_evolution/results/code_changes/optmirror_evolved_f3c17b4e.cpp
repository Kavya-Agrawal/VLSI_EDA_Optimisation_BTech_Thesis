// PV-Evolve Candidate: f3c17b4e2d88
// Target: src/dpl/src/OptMirror.cpp
// WNS improvement: +1.74% on gcd/Nangate45
// PVCC: all 6 layers PASS
// SSPE program: pin_displacement -> orientation_cost -> wirelength_delta

double OptMirror::candidateScore(const MirrorCandidate& c) const
{
  double score = 0.0;

  // Block 0: pin_displacement (TPGM attribution: 38.5%)
  score += c.displacement * (1.0 + 0.12 * c.pin_count);

  // Block 1: orientation_cost (TPGM attribution: 28.1%)
  score += 0.18 * c.orientation_mismatch * c.neighbor_count;

  // Block 2: wirelength_delta (TPGM attribution: 33.4%)
  score += 0.25 * c.estimated_hpwl_delta;

  return score;
}
