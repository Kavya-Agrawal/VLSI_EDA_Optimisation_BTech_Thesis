// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05230643;
  double density_weight = 0.01210713;
  double prefix_weight = 0.04732950;
  double neighborhood_weight = 0.02290092;
  double late_weight = 0.27445046;
  double critical_weight = 0.20990775;
  unsigned budget = 26;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
