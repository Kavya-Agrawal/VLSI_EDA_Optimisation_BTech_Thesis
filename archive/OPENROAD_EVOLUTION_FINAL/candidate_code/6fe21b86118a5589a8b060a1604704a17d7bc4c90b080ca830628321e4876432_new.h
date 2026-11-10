// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58504138;
  double density_weight = 0.14251207;
  double prefix_weight = 0.06953344;
  double neighborhood_weight = 0.28506612;
  double late_weight = 0.03373876;
  double critical_weight = 0.38167234;
  unsigned budget = 25;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
