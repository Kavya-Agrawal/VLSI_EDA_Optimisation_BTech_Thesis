// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83272622;
  double density_weight = 0.39528238;
  double prefix_weight = 0.39359883;
  double neighborhood_weight = 0.37036435;
  double late_weight = 0.09618645;
  double critical_weight = 0.21714107;
  unsigned budget = 38;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
