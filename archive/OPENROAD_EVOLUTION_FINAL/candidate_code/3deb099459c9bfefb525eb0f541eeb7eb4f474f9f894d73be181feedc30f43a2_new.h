// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00506326;
  double density_weight = 0.24616315;
  double prefix_weight = 0.38903124;
  double neighborhood_weight = 0.00654597;
  double late_weight = 0.11594457;
  double critical_weight = 0.18842916;
  unsigned budget = 26;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
