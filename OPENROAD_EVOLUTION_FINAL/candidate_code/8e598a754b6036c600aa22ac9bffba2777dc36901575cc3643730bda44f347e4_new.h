// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29519933;
  double density_weight = 0.35364229;
  double prefix_weight = 0.44922620;
  double neighborhood_weight = 0.34683829;
  double late_weight = 0.15748185;
  double critical_weight = 0.02656800;
  unsigned budget = 9;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
