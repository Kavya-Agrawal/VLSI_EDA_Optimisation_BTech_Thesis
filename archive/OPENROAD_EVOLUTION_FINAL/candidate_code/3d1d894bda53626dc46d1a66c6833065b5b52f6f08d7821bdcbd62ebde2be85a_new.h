// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42584288;
  double density_weight = 0.58597046;
  double prefix_weight = 0.33028360;
  double neighborhood_weight = 0.20960576;
  double late_weight = 0.18448013;
  double critical_weight = 0.21910924;
  unsigned budget = 39;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
