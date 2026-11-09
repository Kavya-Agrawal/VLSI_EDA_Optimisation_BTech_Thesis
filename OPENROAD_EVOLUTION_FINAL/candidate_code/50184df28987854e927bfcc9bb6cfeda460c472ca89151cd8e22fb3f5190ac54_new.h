// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08104494;
  double density_weight = 0.49742973;
  double prefix_weight = 0.13408219;
  double neighborhood_weight = 0.06186148;
  double late_weight = 0.24137250;
  double critical_weight = 0.35027075;
  unsigned budget = 25;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
