// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71362963;
  double density_weight = 0.58585938;
  double prefix_weight = 0.44413585;
  double neighborhood_weight = 0.10885041;
  double late_weight = 0.04225189;
  double critical_weight = 0.07436875;
  unsigned budget = 10;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
