// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98650252;
  double density_weight = 0.05376467;
  double prefix_weight = 0.27583688;
  double neighborhood_weight = 0.18739416;
  double late_weight = 0.17221215;
  double critical_weight = 0.17729093;
  unsigned budget = 31;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
