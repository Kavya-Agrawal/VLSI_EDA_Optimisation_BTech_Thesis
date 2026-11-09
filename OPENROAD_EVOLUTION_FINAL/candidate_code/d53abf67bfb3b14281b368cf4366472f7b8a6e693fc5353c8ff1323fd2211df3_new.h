// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41952685;
  double density_weight = 0.15692022;
  double prefix_weight = 0.15903059;
  double neighborhood_weight = 0.02988842;
  double late_weight = 0.17258613;
  double critical_weight = 0.22850570;
  unsigned budget = 14;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
