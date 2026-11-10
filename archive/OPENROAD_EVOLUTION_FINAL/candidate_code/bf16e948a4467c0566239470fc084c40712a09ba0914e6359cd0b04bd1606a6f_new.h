// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63814213;
  double density_weight = 0.57730336;
  double prefix_weight = 0.39131945;
  double neighborhood_weight = 0.21143224;
  double late_weight = 0.13150810;
  double critical_weight = 0.24592475;
  unsigned budget = 17;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
