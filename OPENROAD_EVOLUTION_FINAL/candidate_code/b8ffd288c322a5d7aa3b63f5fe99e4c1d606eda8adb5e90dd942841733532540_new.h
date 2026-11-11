// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63145588;
  double density_weight = 0.59673815;
  double prefix_weight = 0.06104372;
  double neighborhood_weight = 0.34668169;
  double late_weight = 0.20805049;
  double critical_weight = 0.16114012;
  unsigned budget = 5;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
