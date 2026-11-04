// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11891445;
  double density_weight = 0.47711489;
  double prefix_weight = 0.48796672;
  double neighborhood_weight = 0.11665357;
  double late_weight = 0.05881390;
  double critical_weight = 0.09333234;
  unsigned budget = 34;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
