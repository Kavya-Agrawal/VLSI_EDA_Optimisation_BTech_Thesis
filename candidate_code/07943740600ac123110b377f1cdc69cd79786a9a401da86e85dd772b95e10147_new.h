// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95189015;
  double density_weight = 0.24964994;
  double prefix_weight = 0.02158255;
  double neighborhood_weight = 0.13997199;
  double late_weight = 0.01167733;
  double critical_weight = 0.25192308;
  unsigned budget = 20;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
