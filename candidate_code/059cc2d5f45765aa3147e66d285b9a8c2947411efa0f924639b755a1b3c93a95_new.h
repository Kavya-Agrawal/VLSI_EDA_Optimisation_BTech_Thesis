// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58954548;
  double density_weight = 0.11549627;
  double prefix_weight = 0.19617532;
  double neighborhood_weight = 0.39674613;
  double late_weight = 0.24242130;
  double critical_weight = 0.11193756;
  unsigned budget = 13;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
