// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97094099;
  double density_weight = 0.25774800;
  double prefix_weight = 0.01732976;
  double neighborhood_weight = 0.12095830;
  double late_weight = 0.13407366;
  double critical_weight = 0.06601154;
  unsigned budget = 37;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
