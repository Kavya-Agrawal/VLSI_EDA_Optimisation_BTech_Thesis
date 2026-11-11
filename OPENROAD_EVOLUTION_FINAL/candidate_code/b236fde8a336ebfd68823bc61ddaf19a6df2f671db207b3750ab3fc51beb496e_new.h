// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86212204;
  double density_weight = 0.11679580;
  double prefix_weight = 0.49331092;
  double neighborhood_weight = 0.25915729;
  double late_weight = 0.18373608;
  double critical_weight = 0.32407435;
  unsigned budget = 9;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
