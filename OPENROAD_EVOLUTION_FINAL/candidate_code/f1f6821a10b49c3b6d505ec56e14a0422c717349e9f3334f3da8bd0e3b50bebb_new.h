// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57635827;
  double density_weight = 0.43934321;
  double prefix_weight = 0.16382132;
  double neighborhood_weight = 0.34191505;
  double late_weight = 0.01478152;
  double critical_weight = 0.49813823;
  unsigned budget = 20;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
