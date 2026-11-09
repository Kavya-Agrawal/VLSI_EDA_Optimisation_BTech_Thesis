// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64490594;
  double density_weight = 0.50068602;
  double prefix_weight = 0.29687177;
  double neighborhood_weight = 0.23434446;
  double late_weight = 0.22900232;
  double critical_weight = 0.49592267;
  unsigned budget = 40;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
