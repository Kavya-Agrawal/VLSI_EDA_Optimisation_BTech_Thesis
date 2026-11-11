// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33514936;
  double density_weight = 0.04215904;
  double prefix_weight = 0.40956159;
  double neighborhood_weight = 0.34345412;
  double late_weight = 0.09513207;
  double critical_weight = 0.07310976;
  unsigned budget = 24;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
