// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44235446;
  double density_weight = 0.00467379;
  double prefix_weight = 0.06390678;
  double neighborhood_weight = 0.17837580;
  double late_weight = 0.25784495;
  double critical_weight = 0.14160759;
  unsigned budget = 10;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
