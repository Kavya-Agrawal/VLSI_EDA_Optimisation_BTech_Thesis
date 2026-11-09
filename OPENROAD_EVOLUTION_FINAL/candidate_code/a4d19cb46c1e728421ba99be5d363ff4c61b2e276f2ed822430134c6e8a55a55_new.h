// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07342168;
  double density_weight = 0.57045021;
  double prefix_weight = 0.23456111;
  double neighborhood_weight = 0.01806018;
  double late_weight = 0.00861376;
  double critical_weight = 0.49277589;
  unsigned budget = 11;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
