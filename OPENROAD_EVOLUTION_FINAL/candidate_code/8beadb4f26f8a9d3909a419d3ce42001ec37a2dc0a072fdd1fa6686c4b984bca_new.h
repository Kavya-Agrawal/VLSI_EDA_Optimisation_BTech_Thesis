// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76943452;
  double density_weight = 0.41875645;
  double prefix_weight = 0.10299108;
  double neighborhood_weight = 0.06443591;
  double late_weight = 0.05090958;
  double critical_weight = 0.44137792;
  unsigned budget = 24;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
