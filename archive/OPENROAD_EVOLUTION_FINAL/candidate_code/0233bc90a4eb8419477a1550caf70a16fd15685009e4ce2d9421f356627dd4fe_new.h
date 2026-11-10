// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70926292;
  double density_weight = 0.37069210;
  double prefix_weight = 0.45624229;
  double neighborhood_weight = 0.08780428;
  double late_weight = 0.24595611;
  double critical_weight = 0.35152762;
  unsigned budget = 30;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
