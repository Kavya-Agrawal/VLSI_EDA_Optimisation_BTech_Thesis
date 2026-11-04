// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82660434;
  double density_weight = 0.04260365;
  double prefix_weight = 0.41793116;
  double neighborhood_weight = 0.14656199;
  double late_weight = 0.29980324;
  double critical_weight = 0.49064104;
  unsigned budget = 13;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
