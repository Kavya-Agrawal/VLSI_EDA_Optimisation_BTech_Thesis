// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70154231;
  double density_weight = 0.32342147;
  double prefix_weight = 0.13793699;
  double neighborhood_weight = 0.00815320;
  double late_weight = 0.25055578;
  double critical_weight = 0.00644223;
  unsigned budget = 8;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
