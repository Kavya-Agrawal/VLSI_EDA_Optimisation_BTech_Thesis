// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51654577;
  double density_weight = 0.05771981;
  double prefix_weight = 0.15580195;
  double neighborhood_weight = 0.33541158;
  double late_weight = 0.18478618;
  double critical_weight = 0.23548479;
  unsigned budget = 39;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
