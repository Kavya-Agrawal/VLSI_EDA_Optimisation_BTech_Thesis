// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57451737;
  double density_weight = 0.16312225;
  double prefix_weight = 0.39830001;
  double neighborhood_weight = 0.01535065;
  double late_weight = 0.23906572;
  double critical_weight = 0.13225397;
  unsigned budget = 32;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
