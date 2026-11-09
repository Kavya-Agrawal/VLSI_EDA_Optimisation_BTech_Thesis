// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30037609;
  double density_weight = 0.31645547;
  double prefix_weight = 0.00965249;
  double neighborhood_weight = 0.39714715;
  double late_weight = 0.14032491;
  double critical_weight = 0.44982445;
  unsigned budget = 29;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
