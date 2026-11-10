// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42829948;
  double density_weight = 0.28554231;
  double prefix_weight = 0.29291619;
  double neighborhood_weight = 0.17013794;
  double late_weight = 0.21371336;
  double critical_weight = 0.11082115;
  unsigned budget = 40;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
