// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25874983;
  double density_weight = 0.54662113;
  double prefix_weight = 0.12820928;
  double neighborhood_weight = 0.04117371;
  double late_weight = 0.19690244;
  double critical_weight = 0.49942409;
  unsigned budget = 8;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
