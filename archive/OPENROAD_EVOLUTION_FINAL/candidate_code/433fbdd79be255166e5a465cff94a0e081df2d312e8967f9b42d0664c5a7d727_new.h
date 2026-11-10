// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09854750;
  double density_weight = 0.27629703;
  double prefix_weight = 0.10487852;
  double neighborhood_weight = 0.30901634;
  double late_weight = 0.07167970;
  double critical_weight = 0.44254831;
  unsigned budget = 31;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
