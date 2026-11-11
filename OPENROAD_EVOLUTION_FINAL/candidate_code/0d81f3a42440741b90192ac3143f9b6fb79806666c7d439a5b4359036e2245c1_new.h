// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45121803;
  double density_weight = 0.36051621;
  double prefix_weight = 0.26697077;
  double neighborhood_weight = 0.25977503;
  double late_weight = 0.17296399;
  double critical_weight = 0.18858972;
  unsigned budget = 29;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
