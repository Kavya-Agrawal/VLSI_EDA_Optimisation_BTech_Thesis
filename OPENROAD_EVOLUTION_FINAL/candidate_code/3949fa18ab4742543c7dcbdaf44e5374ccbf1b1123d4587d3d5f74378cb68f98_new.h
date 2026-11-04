// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07233009;
  double density_weight = 0.59269942;
  double prefix_weight = 0.06356629;
  double neighborhood_weight = 0.22806252;
  double late_weight = 0.07124261;
  double critical_weight = 0.02724708;
  unsigned budget = 30;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
