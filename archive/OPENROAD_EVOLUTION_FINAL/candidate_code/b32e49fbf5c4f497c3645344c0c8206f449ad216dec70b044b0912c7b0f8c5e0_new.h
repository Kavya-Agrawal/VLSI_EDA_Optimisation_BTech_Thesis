// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39009654;
  double density_weight = 0.16716947;
  double prefix_weight = 0.13427130;
  double neighborhood_weight = 0.34766081;
  double late_weight = 0.26100898;
  double critical_weight = 0.29852724;
  unsigned budget = 37;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
