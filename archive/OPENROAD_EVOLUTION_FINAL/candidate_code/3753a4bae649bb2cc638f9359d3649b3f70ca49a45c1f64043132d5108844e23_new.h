// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81000973;
  double density_weight = 0.46213683;
  double prefix_weight = 0.27154053;
  double neighborhood_weight = 0.38077632;
  double late_weight = 0.02941824;
  double critical_weight = 0.39865002;
  unsigned budget = 4;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
