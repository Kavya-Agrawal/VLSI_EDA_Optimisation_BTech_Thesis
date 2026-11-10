// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98243894;
  double density_weight = 0.26179237;
  double prefix_weight = 0.49530571;
  double neighborhood_weight = 0.33082999;
  double late_weight = 0.13543542;
  double critical_weight = 0.19629971;
  unsigned budget = 6;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
