// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02294139;
  double density_weight = 0.17955360;
  double prefix_weight = 0.28226547;
  double neighborhood_weight = 0.12863595;
  double late_weight = 0.06353487;
  double critical_weight = 0.25363732;
  unsigned budget = 35;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
