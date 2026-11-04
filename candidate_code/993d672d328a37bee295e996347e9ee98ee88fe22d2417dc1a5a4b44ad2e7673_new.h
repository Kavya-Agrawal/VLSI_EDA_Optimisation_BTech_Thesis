// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78635857;
  double density_weight = 0.19742321;
  double prefix_weight = 0.09653219;
  double neighborhood_weight = 0.25783956;
  double late_weight = 0.27044499;
  double critical_weight = 0.45184259;
  unsigned budget = 21;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
