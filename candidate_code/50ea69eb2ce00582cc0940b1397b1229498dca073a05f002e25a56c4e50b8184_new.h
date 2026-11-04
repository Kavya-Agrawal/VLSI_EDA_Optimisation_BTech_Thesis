// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77795272;
  double density_weight = 0.10771293;
  double prefix_weight = 0.21479165;
  double neighborhood_weight = 0.04308005;
  double late_weight = 0.17253375;
  double critical_weight = 0.38650416;
  unsigned budget = 25;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
