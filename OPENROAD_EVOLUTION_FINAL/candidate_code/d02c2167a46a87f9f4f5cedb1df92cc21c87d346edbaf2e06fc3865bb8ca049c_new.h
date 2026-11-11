// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38249763;
  double density_weight = 0.58075227;
  double prefix_weight = 0.36493975;
  double neighborhood_weight = 0.01714572;
  double late_weight = 0.10681769;
  double critical_weight = 0.01932054;
  unsigned budget = 20;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
