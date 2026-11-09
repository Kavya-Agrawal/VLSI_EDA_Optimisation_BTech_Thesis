// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10794321;
  double density_weight = 0.00835627;
  double prefix_weight = 0.32531106;
  double neighborhood_weight = 0.39838079;
  double late_weight = 0.22632953;
  double critical_weight = 0.27691347;
  unsigned budget = 4;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
