// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07488398;
  double density_weight = 0.01804871;
  double prefix_weight = 0.20504007;
  double neighborhood_weight = 0.29934415;
  double late_weight = 0.11632157;
  double critical_weight = 0.03816903;
  unsigned budget = 20;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
