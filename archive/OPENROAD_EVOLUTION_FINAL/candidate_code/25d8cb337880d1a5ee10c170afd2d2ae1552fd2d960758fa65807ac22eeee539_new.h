// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70206832;
  double density_weight = 0.49472324;
  double prefix_weight = 0.19740072;
  double neighborhood_weight = 0.22583545;
  double late_weight = 0.03428669;
  double critical_weight = 0.45748797;
  unsigned budget = 12;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
