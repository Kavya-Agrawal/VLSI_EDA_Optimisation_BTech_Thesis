// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92110572;
  double density_weight = 0.13934048;
  double prefix_weight = 0.24567932;
  double neighborhood_weight = 0.32367868;
  double late_weight = 0.24038130;
  double critical_weight = 0.40780168;
  unsigned budget = 8;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
