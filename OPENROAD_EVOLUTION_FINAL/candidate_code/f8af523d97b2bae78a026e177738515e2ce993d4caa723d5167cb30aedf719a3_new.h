// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01808613;
  double density_weight = 0.42743603;
  double prefix_weight = 0.42267304;
  double neighborhood_weight = 0.34087868;
  double late_weight = 0.11962113;
  double critical_weight = 0.25347403;
  unsigned budget = 17;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
