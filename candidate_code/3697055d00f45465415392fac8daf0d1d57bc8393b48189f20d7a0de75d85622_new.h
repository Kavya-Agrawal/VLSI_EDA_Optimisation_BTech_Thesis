// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62895690;
  double density_weight = 0.54403201;
  double prefix_weight = 0.24794786;
  double neighborhood_weight = 0.19325946;
  double late_weight = 0.15266717;
  double critical_weight = 0.42771726;
  unsigned budget = 13;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
