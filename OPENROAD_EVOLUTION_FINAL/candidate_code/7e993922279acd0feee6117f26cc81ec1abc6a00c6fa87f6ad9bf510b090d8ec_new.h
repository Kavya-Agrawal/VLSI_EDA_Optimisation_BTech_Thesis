// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81752067;
  double density_weight = 0.11254101;
  double prefix_weight = 0.39426095;
  double neighborhood_weight = 0.29440077;
  double late_weight = 0.15002862;
  double critical_weight = 0.06251384;
  unsigned budget = 28;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
