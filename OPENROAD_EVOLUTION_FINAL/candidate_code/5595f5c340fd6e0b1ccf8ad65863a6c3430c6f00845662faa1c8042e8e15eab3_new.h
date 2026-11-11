// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11767956;
  double density_weight = 0.56107617;
  double prefix_weight = 0.01959780;
  double neighborhood_weight = 0.34546993;
  double late_weight = 0.15153695;
  double critical_weight = 0.06294807;
  unsigned budget = 21;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
