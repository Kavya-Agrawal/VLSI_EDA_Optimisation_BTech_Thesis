// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51655129;
  double density_weight = 0.17638015;
  double prefix_weight = 0.21712387;
  double neighborhood_weight = 0.34308013;
  double late_weight = 0.17423691;
  double critical_weight = 0.45522950;
  unsigned budget = 21;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
