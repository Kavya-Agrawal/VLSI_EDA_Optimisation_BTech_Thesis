// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93346758;
  double density_weight = 0.04773325;
  double prefix_weight = 0.49944531;
  double neighborhood_weight = 0.04581527;
  double late_weight = 0.26276701;
  double critical_weight = 0.13149295;
  unsigned budget = 20;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
