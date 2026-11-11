// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82005031;
  double density_weight = 0.03096775;
  double prefix_weight = 0.14668271;
  double neighborhood_weight = 0.13047488;
  double late_weight = 0.21266292;
  double critical_weight = 0.13891934;
  unsigned budget = 30;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
