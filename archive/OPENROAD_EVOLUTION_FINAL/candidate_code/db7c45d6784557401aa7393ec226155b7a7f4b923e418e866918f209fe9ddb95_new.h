// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66438170;
  double density_weight = 0.42023526;
  double prefix_weight = 0.46214628;
  double neighborhood_weight = 0.08561696;
  double late_weight = 0.21650269;
  double critical_weight = 0.43573685;
  unsigned budget = 12;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
