// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99458695;
  double density_weight = 0.28769654;
  double prefix_weight = 0.31394423;
  double neighborhood_weight = 0.09203695;
  double late_weight = 0.07399121;
  double critical_weight = 0.04552582;
  unsigned budget = 16;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
