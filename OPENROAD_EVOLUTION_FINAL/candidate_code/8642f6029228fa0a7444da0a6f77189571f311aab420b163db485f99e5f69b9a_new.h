// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91477958;
  double density_weight = 0.34874805;
  double prefix_weight = 0.01081596;
  double neighborhood_weight = 0.14457522;
  double late_weight = 0.21553714;
  double critical_weight = 0.29616250;
  unsigned budget = 23;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
