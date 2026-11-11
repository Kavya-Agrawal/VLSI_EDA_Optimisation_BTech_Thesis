// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00968161;
  double density_weight = 0.55363473;
  double prefix_weight = 0.32911277;
  double neighborhood_weight = 0.00013150;
  double late_weight = 0.04643268;
  double critical_weight = 0.14384587;
  unsigned budget = 24;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
