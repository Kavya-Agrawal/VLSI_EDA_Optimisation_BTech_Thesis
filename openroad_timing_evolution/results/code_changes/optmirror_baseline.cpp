// Stock OpenROAD DPL: src/dpl/src/OptMirror.cpp
// Candidate ordering for mirror optimization (baseline)

double OptMirror::candidateScore(const MirrorCandidate& c) const
{
  return c.displacement;
}
