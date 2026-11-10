// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46224183;
  double density_weight = 0.29829441;
  double prefix_weight = 0.05322387;
  double neighborhood_weight = 0.03588513;
  double late_weight = 0.23337835;
  double critical_weight = 0.11086962;
  unsigned budget = 16;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
