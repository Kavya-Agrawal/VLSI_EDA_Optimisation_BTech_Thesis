// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67162732;
  double density_weight = 0.41215997;
  double prefix_weight = 0.33867769;
  double neighborhood_weight = 0.01508535;
  double late_weight = 0.20896883;
  double critical_weight = 0.06739719;
  unsigned budget = 37;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
