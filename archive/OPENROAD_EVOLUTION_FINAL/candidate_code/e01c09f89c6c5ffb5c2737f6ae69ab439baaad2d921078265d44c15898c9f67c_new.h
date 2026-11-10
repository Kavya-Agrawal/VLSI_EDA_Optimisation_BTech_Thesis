// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29327128;
  double density_weight = 0.40298406;
  double prefix_weight = 0.48077572;
  double neighborhood_weight = 0.32577263;
  double late_weight = 0.17643922;
  double critical_weight = 0.34598642;
  unsigned budget = 24;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
