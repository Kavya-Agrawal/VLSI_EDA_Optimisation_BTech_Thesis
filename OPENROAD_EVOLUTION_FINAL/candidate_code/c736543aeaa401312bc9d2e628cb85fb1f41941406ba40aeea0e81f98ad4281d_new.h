// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93413893;
  double density_weight = 0.25958402;
  double prefix_weight = 0.49694567;
  double neighborhood_weight = 0.19470919;
  double late_weight = 0.24918791;
  double critical_weight = 0.37695537;
  unsigned budget = 34;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
