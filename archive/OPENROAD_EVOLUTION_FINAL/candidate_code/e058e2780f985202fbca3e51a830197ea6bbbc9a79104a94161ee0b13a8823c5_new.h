// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09433131;
  double density_weight = 0.39478273;
  double prefix_weight = 0.25860216;
  double neighborhood_weight = 0.38689006;
  double late_weight = 0.04825798;
  double critical_weight = 0.17470046;
  unsigned budget = 19;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
