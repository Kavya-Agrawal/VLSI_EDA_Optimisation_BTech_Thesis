// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15573744;
  double density_weight = 0.54885015;
  double prefix_weight = 0.31415484;
  double neighborhood_weight = 0.34078322;
  double late_weight = 0.01256494;
  double critical_weight = 0.20058938;
  unsigned budget = 19;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
