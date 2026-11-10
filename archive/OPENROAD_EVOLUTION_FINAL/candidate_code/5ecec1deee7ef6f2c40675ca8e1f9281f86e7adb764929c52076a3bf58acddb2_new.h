// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84857846;
  double density_weight = 0.24576450;
  double prefix_weight = 0.00002556;
  double neighborhood_weight = 0.20829288;
  double late_weight = 0.22852131;
  double critical_weight = 0.04338082;
  unsigned budget = 28;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
