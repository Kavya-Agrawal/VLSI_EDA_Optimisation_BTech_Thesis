// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20357536;
  double density_weight = 0.59704448;
  double prefix_weight = 0.41321024;
  double neighborhood_weight = 0.03877774;
  double late_weight = 0.15837797;
  double critical_weight = 0.48631225;
  unsigned budget = 9;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
