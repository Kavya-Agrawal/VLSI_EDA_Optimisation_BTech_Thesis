// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16900463;
  double density_weight = 0.44750046;
  double prefix_weight = 0.15535263;
  double neighborhood_weight = 0.14589716;
  double late_weight = 0.01779767;
  double critical_weight = 0.23348056;
  unsigned budget = 21;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
