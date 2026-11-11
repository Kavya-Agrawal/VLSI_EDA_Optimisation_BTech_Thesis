// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25101642;
  double density_weight = 0.14327557;
  double prefix_weight = 0.47673691;
  double neighborhood_weight = 0.31301583;
  double late_weight = 0.29190836;
  double critical_weight = 0.20240560;
  unsigned budget = 7;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
