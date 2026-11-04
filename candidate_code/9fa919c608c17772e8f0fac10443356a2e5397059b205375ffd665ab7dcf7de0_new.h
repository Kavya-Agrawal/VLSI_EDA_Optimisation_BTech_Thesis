// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96643475;
  double density_weight = 0.05194312;
  double prefix_weight = 0.41145552;
  double neighborhood_weight = 0.37596252;
  double late_weight = 0.11748971;
  double critical_weight = 0.27212776;
  unsigned budget = 4;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
