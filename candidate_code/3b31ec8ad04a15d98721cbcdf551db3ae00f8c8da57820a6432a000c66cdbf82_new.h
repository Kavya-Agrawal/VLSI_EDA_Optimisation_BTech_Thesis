// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70702502;
  double density_weight = 0.32280623;
  double prefix_weight = 0.48718478;
  double neighborhood_weight = 0.22338101;
  double late_weight = 0.04537921;
  double critical_weight = 0.48189326;
  unsigned budget = 22;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
