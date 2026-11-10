// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10961149;
  double density_weight = 0.25409262;
  double prefix_weight = 0.11883775;
  double neighborhood_weight = 0.29992628;
  double late_weight = 0.17858320;
  double critical_weight = 0.40353054;
  unsigned budget = 11;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
