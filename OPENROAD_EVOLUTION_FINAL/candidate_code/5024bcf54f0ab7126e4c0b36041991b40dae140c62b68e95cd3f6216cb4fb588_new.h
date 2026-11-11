// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22516438;
  double density_weight = 0.07227284;
  double prefix_weight = 0.35323031;
  double neighborhood_weight = 0.30588706;
  double late_weight = 0.02209441;
  double critical_weight = 0.06710013;
  unsigned budget = 30;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
