// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84068716;
  double density_weight = 0.05023326;
  double prefix_weight = 0.33741518;
  double neighborhood_weight = 0.39039519;
  double late_weight = 0.26551301;
  double critical_weight = 0.20131713;
  unsigned budget = 8;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
