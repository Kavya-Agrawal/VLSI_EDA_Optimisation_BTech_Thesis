// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24915697;
  double density_weight = 0.24544525;
  double prefix_weight = 0.33661572;
  double neighborhood_weight = 0.18931014;
  double late_weight = 0.29609346;
  double critical_weight = 0.09105253;
  unsigned budget = 4;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
