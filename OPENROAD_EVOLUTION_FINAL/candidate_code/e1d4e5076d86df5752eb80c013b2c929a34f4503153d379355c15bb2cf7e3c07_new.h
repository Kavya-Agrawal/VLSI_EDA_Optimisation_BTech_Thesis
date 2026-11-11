// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73232968;
  double density_weight = 0.13022478;
  double prefix_weight = 0.28145495;
  double neighborhood_weight = 0.09424945;
  double late_weight = 0.26298703;
  double critical_weight = 0.12106893;
  unsigned budget = 28;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
