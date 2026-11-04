// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21680535;
  double density_weight = 0.37004528;
  double prefix_weight = 0.32610963;
  double neighborhood_weight = 0.17315155;
  double late_weight = 0.05121218;
  double critical_weight = 0.33505998;
  unsigned budget = 14;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
