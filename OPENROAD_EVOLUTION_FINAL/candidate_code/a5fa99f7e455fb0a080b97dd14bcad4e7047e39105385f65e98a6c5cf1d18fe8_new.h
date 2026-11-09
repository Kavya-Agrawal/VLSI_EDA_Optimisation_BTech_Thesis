// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06393235;
  double density_weight = 0.48832923;
  double prefix_weight = 0.14261600;
  double neighborhood_weight = 0.17373941;
  double late_weight = 0.06727288;
  double critical_weight = 0.37903109;
  unsigned budget = 14;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
