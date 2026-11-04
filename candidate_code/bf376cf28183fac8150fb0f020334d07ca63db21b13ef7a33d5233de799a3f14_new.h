// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86212552;
  double density_weight = 0.48207900;
  double prefix_weight = 0.14858278;
  double neighborhood_weight = 0.37981661;
  double late_weight = 0.25593161;
  double critical_weight = 0.16439159;
  unsigned budget = 30;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
