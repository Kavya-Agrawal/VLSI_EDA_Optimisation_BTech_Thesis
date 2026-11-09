// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94690205;
  double density_weight = 0.09210252;
  double prefix_weight = 0.20179567;
  double neighborhood_weight = 0.21183983;
  double late_weight = 0.13837623;
  double critical_weight = 0.28255006;
  unsigned budget = 13;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
