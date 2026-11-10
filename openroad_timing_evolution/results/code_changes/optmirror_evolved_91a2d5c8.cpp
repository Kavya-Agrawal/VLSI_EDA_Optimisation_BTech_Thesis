// PV-Evolve Candidate: 91a2d5c83f19
// Target: src/dpl/src/OptMirror.cpp
// WNS improvement: +1.31% on gcd/Nangate45
// PVCC: all 6 layers PASS
// SSPE program: pin_displacement -> wirelength_delta

double OptMirror::candidateScore(const MirrorCandidate& c) const
{
  double score = 0.0;

  // Block 0: pin_displacement
  score += c.displacement * (1.0 + 0.08 * c.pin_count);

  // Block 1: wirelength_delta
  score += 0.20 * c.estimated_hpwl_delta;

  return score;
}
