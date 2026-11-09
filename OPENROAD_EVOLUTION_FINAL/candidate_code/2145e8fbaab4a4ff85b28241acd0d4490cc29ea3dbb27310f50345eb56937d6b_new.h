// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94278029;
  double density_weight = 0.36447049;
  double prefix_weight = 0.20798849;
  double neighborhood_weight = 0.39974163;
  double late_weight = 0.04594290;
  double critical_weight = 0.37608298;
  unsigned budget = 39;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
