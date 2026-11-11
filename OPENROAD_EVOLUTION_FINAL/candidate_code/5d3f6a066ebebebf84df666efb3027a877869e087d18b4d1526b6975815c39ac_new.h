// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39854550;
  double density_weight = 0.46945641;
  double prefix_weight = 0.17151447;
  double neighborhood_weight = 0.17605834;
  double late_weight = 0.17225486;
  double critical_weight = 0.05746731;
  unsigned budget = 10;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
