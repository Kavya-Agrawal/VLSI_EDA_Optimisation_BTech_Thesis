// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89194169;
  double density_weight = 0.28704781;
  double prefix_weight = 0.02399872;
  double neighborhood_weight = 0.34870503;
  double late_weight = 0.06547336;
  double critical_weight = 0.21818390;
  unsigned budget = 20;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
