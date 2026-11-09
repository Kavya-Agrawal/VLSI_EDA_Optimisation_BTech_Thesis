// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91101194;
  double density_weight = 0.13132004;
  double prefix_weight = 0.38546368;
  double neighborhood_weight = 0.21142611;
  double late_weight = 0.19586354;
  double critical_weight = 0.12176171;
  unsigned budget = 12;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
