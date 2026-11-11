// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58523098;
  double density_weight = 0.28110917;
  double prefix_weight = 0.24554171;
  double neighborhood_weight = 0.09808151;
  double late_weight = 0.10554548;
  double critical_weight = 0.43092548;
  unsigned budget = 26;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
