// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73644059;
  double density_weight = 0.05153604;
  double prefix_weight = 0.33989384;
  double neighborhood_weight = 0.07630672;
  double late_weight = 0.22917879;
  double critical_weight = 0.03301720;
  unsigned budget = 8;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
