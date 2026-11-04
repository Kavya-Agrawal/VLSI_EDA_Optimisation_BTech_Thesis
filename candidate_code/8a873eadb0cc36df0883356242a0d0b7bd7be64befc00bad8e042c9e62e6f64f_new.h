// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24173609;
  double density_weight = 0.26028431;
  double prefix_weight = 0.37575537;
  double neighborhood_weight = 0.36443366;
  double late_weight = 0.13273639;
  double critical_weight = 0.35814201;
  unsigned budget = 16;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
