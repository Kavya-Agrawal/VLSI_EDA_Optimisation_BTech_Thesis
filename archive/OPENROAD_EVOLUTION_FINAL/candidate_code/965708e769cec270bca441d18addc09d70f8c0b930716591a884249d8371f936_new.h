// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10908590;
  double density_weight = 0.50785552;
  double prefix_weight = 0.03701507;
  double neighborhood_weight = 0.11625329;
  double late_weight = 0.29761616;
  double critical_weight = 0.38054595;
  unsigned budget = 28;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
