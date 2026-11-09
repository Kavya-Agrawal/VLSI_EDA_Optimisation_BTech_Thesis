// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13939604;
  double density_weight = 0.40983071;
  double prefix_weight = 0.44302602;
  double neighborhood_weight = 0.38690844;
  double late_weight = 0.09274205;
  double critical_weight = 0.43278398;
  unsigned budget = 25;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
