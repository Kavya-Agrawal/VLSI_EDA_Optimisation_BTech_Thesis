// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63603682;
  double density_weight = 0.40568402;
  double prefix_weight = 0.20203783;
  double neighborhood_weight = 0.03467622;
  double late_weight = 0.27049252;
  double critical_weight = 0.05251366;
  unsigned budget = 35;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
