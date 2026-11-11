// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90811571;
  double density_weight = 0.32119435;
  double prefix_weight = 0.21456999;
  double neighborhood_weight = 0.29653858;
  double late_weight = 0.11943824;
  double critical_weight = 0.10883923;
  unsigned budget = 34;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
