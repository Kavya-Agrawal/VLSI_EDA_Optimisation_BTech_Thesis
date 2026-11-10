// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95565611;
  double density_weight = 0.44221465;
  double prefix_weight = 0.44115276;
  double neighborhood_weight = 0.02992545;
  double late_weight = 0.27481334;
  double critical_weight = 0.18509939;
  unsigned budget = 16;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
