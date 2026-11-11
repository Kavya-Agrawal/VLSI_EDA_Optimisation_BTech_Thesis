// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73446620;
  double density_weight = 0.08353578;
  double prefix_weight = 0.32043039;
  double neighborhood_weight = 0.31192540;
  double late_weight = 0.28293728;
  double critical_weight = 0.32093101;
  unsigned budget = 10;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
