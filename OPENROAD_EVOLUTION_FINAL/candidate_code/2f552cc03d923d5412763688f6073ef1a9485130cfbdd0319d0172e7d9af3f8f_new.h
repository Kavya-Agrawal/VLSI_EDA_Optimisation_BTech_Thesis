// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05445102;
  double density_weight = 0.50219773;
  double prefix_weight = 0.06399945;
  double neighborhood_weight = 0.39908563;
  double late_weight = 0.24662267;
  double critical_weight = 0.15229603;
  unsigned budget = 9;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
