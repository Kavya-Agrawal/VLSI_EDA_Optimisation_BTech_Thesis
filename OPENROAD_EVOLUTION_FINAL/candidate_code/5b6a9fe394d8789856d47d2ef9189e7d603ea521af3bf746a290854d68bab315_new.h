// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65859293;
  double density_weight = 0.56856318;
  double prefix_weight = 0.44851247;
  double neighborhood_weight = 0.01769275;
  double late_weight = 0.27806549;
  double critical_weight = 0.44760677;
  unsigned budget = 30;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
