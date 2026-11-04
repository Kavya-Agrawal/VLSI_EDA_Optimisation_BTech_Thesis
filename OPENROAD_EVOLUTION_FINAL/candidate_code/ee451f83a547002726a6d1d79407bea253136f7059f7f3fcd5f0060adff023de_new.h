// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16003804;
  double density_weight = 0.40050641;
  double prefix_weight = 0.21882136;
  double neighborhood_weight = 0.33086099;
  double late_weight = 0.12671808;
  double critical_weight = 0.07308498;
  unsigned budget = 29;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
