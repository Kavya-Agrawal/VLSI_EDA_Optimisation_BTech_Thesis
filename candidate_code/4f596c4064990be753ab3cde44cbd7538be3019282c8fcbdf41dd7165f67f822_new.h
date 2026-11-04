// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89065524;
  double density_weight = 0.46401398;
  double prefix_weight = 0.43850742;
  double neighborhood_weight = 0.09449676;
  double late_weight = 0.20598080;
  double critical_weight = 0.07535698;
  unsigned budget = 31;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
