// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56917737;
  double density_weight = 0.28323026;
  double prefix_weight = 0.24897572;
  double neighborhood_weight = 0.02439771;
  double late_weight = 0.01028855;
  double critical_weight = 0.24782060;
  unsigned budget = 20;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
