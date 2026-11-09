// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89698945;
  double density_weight = 0.51065167;
  double prefix_weight = 0.14979390;
  double neighborhood_weight = 0.32643318;
  double late_weight = 0.19103367;
  double critical_weight = 0.45204984;
  unsigned budget = 20;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
