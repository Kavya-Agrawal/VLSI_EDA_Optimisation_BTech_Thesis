// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74097650;
  double density_weight = 0.35912002;
  double prefix_weight = 0.03419701;
  double neighborhood_weight = 0.01717307;
  double late_weight = 0.24920988;
  double critical_weight = 0.04053257;
  unsigned budget = 35;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
