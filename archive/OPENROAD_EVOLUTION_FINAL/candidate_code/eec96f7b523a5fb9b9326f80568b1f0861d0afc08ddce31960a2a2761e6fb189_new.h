// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89627805;
  double density_weight = 0.44521640;
  double prefix_weight = 0.06507201;
  double neighborhood_weight = 0.12982731;
  double late_weight = 0.19706469;
  double critical_weight = 0.44450358;
  unsigned budget = 36;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
