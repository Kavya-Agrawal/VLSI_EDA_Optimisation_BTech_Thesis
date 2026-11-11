// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86145831;
  double density_weight = 0.46329264;
  double prefix_weight = 0.01956078;
  double neighborhood_weight = 0.14652636;
  double late_weight = 0.17357337;
  double critical_weight = 0.15496174;
  unsigned budget = 10;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
