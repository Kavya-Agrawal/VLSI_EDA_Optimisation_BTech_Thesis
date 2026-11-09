// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73049908;
  double density_weight = 0.44317838;
  double prefix_weight = 0.26089327;
  double neighborhood_weight = 0.37180113;
  double late_weight = 0.29251000;
  double critical_weight = 0.01632159;
  unsigned budget = 23;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
