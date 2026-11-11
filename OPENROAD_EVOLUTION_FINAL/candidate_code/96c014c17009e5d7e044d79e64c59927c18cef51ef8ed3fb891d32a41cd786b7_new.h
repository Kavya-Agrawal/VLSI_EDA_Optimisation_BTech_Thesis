// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92907384;
  double density_weight = 0.51926758;
  double prefix_weight = 0.49840028;
  double neighborhood_weight = 0.05074106;
  double late_weight = 0.01367215;
  double critical_weight = 0.43142875;
  unsigned budget = 21;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
