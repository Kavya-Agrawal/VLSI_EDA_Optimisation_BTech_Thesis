// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46944511;
  double density_weight = 0.37592971;
  double prefix_weight = 0.07792486;
  double neighborhood_weight = 0.33748978;
  double late_weight = 0.14771186;
  double critical_weight = 0.28394905;
  unsigned budget = 15;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
