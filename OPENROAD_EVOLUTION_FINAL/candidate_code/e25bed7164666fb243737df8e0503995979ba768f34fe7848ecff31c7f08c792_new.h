// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96781606;
  double density_weight = 0.12498343;
  double prefix_weight = 0.45994692;
  double neighborhood_weight = 0.27679597;
  double late_weight = 0.21661835;
  double critical_weight = 0.28788178;
  unsigned budget = 17;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
