// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43107365;
  double density_weight = 0.41927653;
  double prefix_weight = 0.42652754;
  double neighborhood_weight = 0.22035820;
  double late_weight = 0.23392715;
  double critical_weight = 0.23191697;
  unsigned budget = 11;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
