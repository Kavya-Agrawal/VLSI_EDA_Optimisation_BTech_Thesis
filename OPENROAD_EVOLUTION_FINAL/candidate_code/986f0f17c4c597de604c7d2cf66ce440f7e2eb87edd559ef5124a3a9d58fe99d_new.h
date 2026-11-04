// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94315422;
  double density_weight = 0.06415682;
  double prefix_weight = 0.45736712;
  double neighborhood_weight = 0.27957407;
  double late_weight = 0.24979030;
  double critical_weight = 0.23863798;
  unsigned budget = 34;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
