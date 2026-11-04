// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75457450;
  double density_weight = 0.50582677;
  double prefix_weight = 0.13850987;
  double neighborhood_weight = 0.35334910;
  double late_weight = 0.16531126;
  double critical_weight = 0.31503425;
  unsigned budget = 6;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
