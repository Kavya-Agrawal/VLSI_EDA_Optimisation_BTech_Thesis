// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50863213;
  double density_weight = 0.13756028;
  double prefix_weight = 0.28643447;
  double neighborhood_weight = 0.00709269;
  double late_weight = 0.13657981;
  double critical_weight = 0.01797682;
  unsigned budget = 4;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
