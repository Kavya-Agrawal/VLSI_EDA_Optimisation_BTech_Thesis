// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91839884;
  double density_weight = 0.45332549;
  double prefix_weight = 0.24557620;
  double neighborhood_weight = 0.39838068;
  double late_weight = 0.12136792;
  double critical_weight = 0.19633479;
  unsigned budget = 9;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
