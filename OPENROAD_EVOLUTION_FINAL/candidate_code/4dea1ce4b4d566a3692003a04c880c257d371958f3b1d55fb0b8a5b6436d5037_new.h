// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76725993;
  double density_weight = 0.34074531;
  double prefix_weight = 0.40861122;
  double neighborhood_weight = 0.28900911;
  double late_weight = 0.19688050;
  double critical_weight = 0.22547615;
  unsigned budget = 12;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
