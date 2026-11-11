// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98824597;
  double density_weight = 0.51562967;
  double prefix_weight = 0.02757961;
  double neighborhood_weight = 0.13553605;
  double late_weight = 0.11716079;
  double critical_weight = 0.29089989;
  unsigned budget = 24;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
