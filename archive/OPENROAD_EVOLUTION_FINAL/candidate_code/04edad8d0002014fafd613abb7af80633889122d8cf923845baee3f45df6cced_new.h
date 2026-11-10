// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87179467;
  double density_weight = 0.38359273;
  double prefix_weight = 0.00969945;
  double neighborhood_weight = 0.24642970;
  double late_weight = 0.01424648;
  double critical_weight = 0.18263572;
  unsigned budget = 14;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
