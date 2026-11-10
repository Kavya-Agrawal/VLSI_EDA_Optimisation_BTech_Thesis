// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28004969;
  double density_weight = 0.44126012;
  double prefix_weight = 0.36136733;
  double neighborhood_weight = 0.39385918;
  double late_weight = 0.29537984;
  double critical_weight = 0.01919712;
  unsigned budget = 37;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
