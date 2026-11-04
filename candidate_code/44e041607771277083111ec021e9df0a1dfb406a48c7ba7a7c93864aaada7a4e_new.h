// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01027646;
  double density_weight = 0.37291075;
  double prefix_weight = 0.00517942;
  double neighborhood_weight = 0.19024409;
  double late_weight = 0.15868218;
  double critical_weight = 0.05072563;
  unsigned budget = 12;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
