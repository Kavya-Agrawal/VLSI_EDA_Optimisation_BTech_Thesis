// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50532909;
  double density_weight = 0.44836800;
  double prefix_weight = 0.32859866;
  double neighborhood_weight = 0.13644910;
  double late_weight = 0.03052960;
  double critical_weight = 0.19862586;
  unsigned budget = 7;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
