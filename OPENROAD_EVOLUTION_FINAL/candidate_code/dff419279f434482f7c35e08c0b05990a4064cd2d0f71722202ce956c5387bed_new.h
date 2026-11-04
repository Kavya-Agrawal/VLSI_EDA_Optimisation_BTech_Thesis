// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16133092;
  double density_weight = 0.27154326;
  double prefix_weight = 0.07375846;
  double neighborhood_weight = 0.01158920;
  double late_weight = 0.14018096;
  double critical_weight = 0.19631516;
  unsigned budget = 36;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
