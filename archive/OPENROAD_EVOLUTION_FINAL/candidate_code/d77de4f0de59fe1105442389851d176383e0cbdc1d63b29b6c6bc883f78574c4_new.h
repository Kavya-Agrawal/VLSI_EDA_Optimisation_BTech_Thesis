// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94568026;
  double density_weight = 0.28648215;
  double prefix_weight = 0.23158988;
  double neighborhood_weight = 0.32114683;
  double late_weight = 0.22271369;
  double critical_weight = 0.11461663;
  unsigned budget = 39;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
