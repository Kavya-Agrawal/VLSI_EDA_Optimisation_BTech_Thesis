// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64608333;
  double density_weight = 0.48710664;
  double prefix_weight = 0.37810069;
  double neighborhood_weight = 0.16424334;
  double late_weight = 0.05348167;
  double critical_weight = 0.15351946;
  unsigned budget = 27;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
