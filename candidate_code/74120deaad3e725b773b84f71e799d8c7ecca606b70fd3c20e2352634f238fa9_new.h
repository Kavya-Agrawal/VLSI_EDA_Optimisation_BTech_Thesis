// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81497867;
  double density_weight = 0.02760472;
  double prefix_weight = 0.29361948;
  double neighborhood_weight = 0.33392385;
  double late_weight = 0.08742567;
  double critical_weight = 0.47411696;
  unsigned budget = 11;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
