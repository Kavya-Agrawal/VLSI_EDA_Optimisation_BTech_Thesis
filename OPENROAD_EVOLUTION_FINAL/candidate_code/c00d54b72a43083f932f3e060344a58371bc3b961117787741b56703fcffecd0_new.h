// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54099535;
  double density_weight = 0.08518714;
  double prefix_weight = 0.36319835;
  double neighborhood_weight = 0.16488609;
  double late_weight = 0.14961672;
  double critical_weight = 0.34889375;
  unsigned budget = 26;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
