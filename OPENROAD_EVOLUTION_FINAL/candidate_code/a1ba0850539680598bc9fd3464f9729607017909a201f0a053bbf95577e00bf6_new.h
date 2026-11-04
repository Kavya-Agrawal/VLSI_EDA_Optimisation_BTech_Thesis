// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29040340;
  double density_weight = 0.20376364;
  double prefix_weight = 0.39330528;
  double neighborhood_weight = 0.03860353;
  double late_weight = 0.05988464;
  double critical_weight = 0.28962607;
  unsigned budget = 20;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
