// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62245936;
  double density_weight = 0.19673122;
  double prefix_weight = 0.48973547;
  double neighborhood_weight = 0.23407223;
  double late_weight = 0.07016590;
  double critical_weight = 0.18036918;
  unsigned budget = 18;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
