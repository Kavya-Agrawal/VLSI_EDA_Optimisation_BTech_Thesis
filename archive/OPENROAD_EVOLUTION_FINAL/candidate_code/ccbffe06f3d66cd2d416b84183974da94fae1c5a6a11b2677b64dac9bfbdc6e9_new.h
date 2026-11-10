// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02621389;
  double density_weight = 0.13990361;
  double prefix_weight = 0.15908314;
  double neighborhood_weight = 0.03740756;
  double late_weight = 0.04873239;
  double critical_weight = 0.01001278;
  unsigned budget = 25;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
