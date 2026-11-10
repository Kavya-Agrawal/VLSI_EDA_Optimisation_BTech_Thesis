// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62582587;
  double density_weight = 0.05669464;
  double prefix_weight = 0.35938887;
  double neighborhood_weight = 0.34147498;
  double late_weight = 0.07965916;
  double critical_weight = 0.27070538;
  unsigned budget = 30;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
