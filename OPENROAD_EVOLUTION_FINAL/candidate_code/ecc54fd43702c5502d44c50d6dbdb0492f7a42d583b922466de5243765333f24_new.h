// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92834212;
  double density_weight = 0.47603190;
  double prefix_weight = 0.36561242;
  double neighborhood_weight = 0.39357832;
  double late_weight = 0.03799606;
  double critical_weight = 0.23694165;
  unsigned budget = 10;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
