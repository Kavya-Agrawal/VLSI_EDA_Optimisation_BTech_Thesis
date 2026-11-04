// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57498790;
  double density_weight = 0.42550290;
  double prefix_weight = 0.47519398;
  double neighborhood_weight = 0.12572551;
  double late_weight = 0.01327255;
  double critical_weight = 0.29262760;
  unsigned budget = 15;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
