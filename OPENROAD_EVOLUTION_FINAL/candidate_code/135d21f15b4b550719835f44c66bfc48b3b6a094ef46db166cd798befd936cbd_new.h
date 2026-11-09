// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12352520;
  double density_weight = 0.33179884;
  double prefix_weight = 0.42593461;
  double neighborhood_weight = 0.38346310;
  double late_weight = 0.18436275;
  double critical_weight = 0.28848619;
  unsigned budget = 12;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
