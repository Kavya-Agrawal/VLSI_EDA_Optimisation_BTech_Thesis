// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98461570;
  double density_weight = 0.18513349;
  double prefix_weight = 0.24369066;
  double neighborhood_weight = 0.36928046;
  double late_weight = 0.17082828;
  double critical_weight = 0.03807896;
  unsigned budget = 24;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
