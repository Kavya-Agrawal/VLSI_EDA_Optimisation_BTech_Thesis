// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61586136;
  double density_weight = 0.24789338;
  double prefix_weight = 0.26883218;
  double neighborhood_weight = 0.22279749;
  double late_weight = 0.28870524;
  double critical_weight = 0.39536829;
  unsigned budget = 26;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
