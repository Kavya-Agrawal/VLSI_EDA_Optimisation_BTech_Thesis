// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28902817;
  double density_weight = 0.52550397;
  double prefix_weight = 0.21274227;
  double neighborhood_weight = 0.04716133;
  double late_weight = 0.02577549;
  double critical_weight = 0.15368680;
  unsigned budget = 31;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
