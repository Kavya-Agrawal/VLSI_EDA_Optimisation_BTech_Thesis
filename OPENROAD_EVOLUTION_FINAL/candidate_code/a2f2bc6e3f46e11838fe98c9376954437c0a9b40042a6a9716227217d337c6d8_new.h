// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51966261;
  double density_weight = 0.10897650;
  double prefix_weight = 0.04014805;
  double neighborhood_weight = 0.14047503;
  double late_weight = 0.20418404;
  double critical_weight = 0.24716319;
  unsigned budget = 28;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
