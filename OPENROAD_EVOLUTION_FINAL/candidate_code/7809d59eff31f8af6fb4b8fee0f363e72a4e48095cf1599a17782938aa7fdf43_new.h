// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27075614;
  double density_weight = 0.32599961;
  double prefix_weight = 0.00311970;
  double neighborhood_weight = 0.36675652;
  double late_weight = 0.13008892;
  double critical_weight = 0.41201849;
  unsigned budget = 6;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
