// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40310850;
  double density_weight = 0.02946404;
  double prefix_weight = 0.27239289;
  double neighborhood_weight = 0.29147516;
  double late_weight = 0.06964215;
  double critical_weight = 0.07247360;
  unsigned budget = 31;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
