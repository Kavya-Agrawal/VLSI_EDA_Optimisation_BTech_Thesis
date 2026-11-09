// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76137887;
  double density_weight = 0.37842598;
  double prefix_weight = 0.09300841;
  double neighborhood_weight = 0.20721208;
  double late_weight = 0.13625846;
  double critical_weight = 0.02909643;
  unsigned budget = 19;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
