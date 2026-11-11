// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36532290;
  double density_weight = 0.52262002;
  double prefix_weight = 0.31914586;
  double neighborhood_weight = 0.04530447;
  double late_weight = 0.26370268;
  double critical_weight = 0.36953934;
  unsigned budget = 28;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
