// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47649742;
  double density_weight = 0.17368392;
  double prefix_weight = 0.06432753;
  double neighborhood_weight = 0.36716463;
  double late_weight = 0.05581978;
  double critical_weight = 0.01573894;
  unsigned budget = 4;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
