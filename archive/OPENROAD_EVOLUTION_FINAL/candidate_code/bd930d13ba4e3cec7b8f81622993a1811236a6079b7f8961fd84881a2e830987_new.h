// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02461465;
  double density_weight = 0.20014841;
  double prefix_weight = 0.07540896;
  double neighborhood_weight = 0.01377182;
  double late_weight = 0.25553646;
  double critical_weight = 0.33387251;
  unsigned budget = 11;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
