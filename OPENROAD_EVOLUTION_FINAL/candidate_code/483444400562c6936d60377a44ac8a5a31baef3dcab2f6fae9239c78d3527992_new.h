// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88173217;
  double density_weight = 0.05706844;
  double prefix_weight = 0.20046309;
  double neighborhood_weight = 0.02377885;
  double late_weight = 0.02773400;
  double critical_weight = 0.17712783;
  unsigned budget = 34;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
