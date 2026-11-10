// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65899599;
  double density_weight = 0.37368209;
  double prefix_weight = 0.24374016;
  double neighborhood_weight = 0.06686650;
  double late_weight = 0.11479907;
  double critical_weight = 0.28429234;
  unsigned budget = 8;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
