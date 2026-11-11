// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13058963;
  double density_weight = 0.13682999;
  double prefix_weight = 0.00241824;
  double neighborhood_weight = 0.34735377;
  double late_weight = 0.02603916;
  double critical_weight = 0.20104298;
  unsigned budget = 25;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
