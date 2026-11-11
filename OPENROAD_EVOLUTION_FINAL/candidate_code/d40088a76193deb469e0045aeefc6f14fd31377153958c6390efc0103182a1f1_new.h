// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85786347;
  double density_weight = 0.24174709;
  double prefix_weight = 0.19769417;
  double neighborhood_weight = 0.19618907;
  double late_weight = 0.05948950;
  double critical_weight = 0.41263202;
  unsigned budget = 9;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
