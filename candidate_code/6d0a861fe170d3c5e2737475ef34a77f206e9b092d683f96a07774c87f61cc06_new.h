// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79883133;
  double density_weight = 0.36287795;
  double prefix_weight = 0.32770182;
  double neighborhood_weight = 0.39753778;
  double late_weight = 0.28198173;
  double critical_weight = 0.46216098;
  unsigned budget = 8;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
