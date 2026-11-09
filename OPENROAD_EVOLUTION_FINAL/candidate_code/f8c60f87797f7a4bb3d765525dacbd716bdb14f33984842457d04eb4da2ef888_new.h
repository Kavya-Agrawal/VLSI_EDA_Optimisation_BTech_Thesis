// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58839558;
  double density_weight = 0.49317769;
  double prefix_weight = 0.27159892;
  double neighborhood_weight = 0.18838815;
  double late_weight = 0.12619528;
  double critical_weight = 0.29897615;
  unsigned budget = 20;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
