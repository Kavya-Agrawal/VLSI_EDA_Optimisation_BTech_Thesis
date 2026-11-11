// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78273267;
  double density_weight = 0.32815351;
  double prefix_weight = 0.18260337;
  double neighborhood_weight = 0.01450127;
  double late_weight = 0.28865152;
  double critical_weight = 0.04521422;
  unsigned budget = 27;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
