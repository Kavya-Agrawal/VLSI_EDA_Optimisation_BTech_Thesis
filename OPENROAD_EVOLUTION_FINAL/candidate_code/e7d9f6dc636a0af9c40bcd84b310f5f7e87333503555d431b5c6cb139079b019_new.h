// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50274774;
  double density_weight = 0.13207561;
  double prefix_weight = 0.48937542;
  double neighborhood_weight = 0.22469616;
  double late_weight = 0.05043280;
  double critical_weight = 0.03168823;
  unsigned budget = 18;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
