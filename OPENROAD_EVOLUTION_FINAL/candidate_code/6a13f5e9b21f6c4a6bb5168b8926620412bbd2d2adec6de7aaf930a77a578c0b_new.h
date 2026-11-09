// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04375875;
  double density_weight = 0.32263304;
  double prefix_weight = 0.33589225;
  double neighborhood_weight = 0.33289124;
  double late_weight = 0.17815330;
  double critical_weight = 0.17381949;
  unsigned budget = 5;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
