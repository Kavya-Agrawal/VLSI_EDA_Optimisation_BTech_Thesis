// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17877580;
  double density_weight = 0.31439870;
  double prefix_weight = 0.20431586;
  double neighborhood_weight = 0.21060565;
  double late_weight = 0.19997266;
  double critical_weight = 0.19470447;
  unsigned budget = 37;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
