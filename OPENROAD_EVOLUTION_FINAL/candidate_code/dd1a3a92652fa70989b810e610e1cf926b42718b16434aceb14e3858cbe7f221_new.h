// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14730392;
  double density_weight = 0.30515409;
  double prefix_weight = 0.00467920;
  double neighborhood_weight = 0.30876642;
  double late_weight = 0.07248424;
  double critical_weight = 0.33045117;
  unsigned budget = 25;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
