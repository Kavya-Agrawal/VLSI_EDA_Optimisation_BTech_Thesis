// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46004487;
  double density_weight = 0.12081824;
  double prefix_weight = 0.00335834;
  double neighborhood_weight = 0.28372397;
  double late_weight = 0.08668999;
  double critical_weight = 0.37042327;
  unsigned budget = 33;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
