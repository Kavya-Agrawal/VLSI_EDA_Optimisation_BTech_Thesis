// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07350229;
  double density_weight = 0.23019388;
  double prefix_weight = 0.14083806;
  double neighborhood_weight = 0.07710757;
  double late_weight = 0.02253419;
  double critical_weight = 0.37932118;
  unsigned budget = 26;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
