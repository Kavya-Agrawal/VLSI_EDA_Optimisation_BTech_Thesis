// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25822450;
  double density_weight = 0.01835483;
  double prefix_weight = 0.20349720;
  double neighborhood_weight = 0.02799752;
  double late_weight = 0.28461902;
  double critical_weight = 0.17790446;
  unsigned budget = 28;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
