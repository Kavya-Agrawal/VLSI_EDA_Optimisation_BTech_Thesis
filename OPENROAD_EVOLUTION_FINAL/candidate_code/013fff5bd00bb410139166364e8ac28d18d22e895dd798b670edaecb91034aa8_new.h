// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71311716;
  double density_weight = 0.36665015;
  double prefix_weight = 0.03933775;
  double neighborhood_weight = 0.13642804;
  double late_weight = 0.15693941;
  double critical_weight = 0.48358113;
  unsigned budget = 26;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
