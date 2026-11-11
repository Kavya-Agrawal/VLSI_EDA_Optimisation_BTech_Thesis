// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01056852;
  double density_weight = 0.52982319;
  double prefix_weight = 0.26242320;
  double neighborhood_weight = 0.07020505;
  double late_weight = 0.28437400;
  double critical_weight = 0.03617542;
  unsigned budget = 18;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
