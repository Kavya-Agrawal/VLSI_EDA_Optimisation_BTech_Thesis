// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47922165;
  double density_weight = 0.07102566;
  double prefix_weight = 0.38502349;
  double neighborhood_weight = 0.30675597;
  double late_weight = 0.15530772;
  double critical_weight = 0.34635070;
  unsigned budget = 23;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
