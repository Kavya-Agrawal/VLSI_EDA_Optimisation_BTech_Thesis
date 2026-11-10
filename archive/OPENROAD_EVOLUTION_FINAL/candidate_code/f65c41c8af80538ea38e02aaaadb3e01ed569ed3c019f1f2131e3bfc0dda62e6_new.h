// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16655012;
  double density_weight = 0.33806033;
  double prefix_weight = 0.39921241;
  double neighborhood_weight = 0.14705902;
  double late_weight = 0.04806042;
  double critical_weight = 0.34758254;
  unsigned budget = 35;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
