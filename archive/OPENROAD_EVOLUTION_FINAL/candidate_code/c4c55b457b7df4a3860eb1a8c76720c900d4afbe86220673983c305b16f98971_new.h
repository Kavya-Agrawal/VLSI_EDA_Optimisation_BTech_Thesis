// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21913827;
  double density_weight = 0.33378804;
  double prefix_weight = 0.12049772;
  double neighborhood_weight = 0.31264342;
  double late_weight = 0.23863180;
  double critical_weight = 0.00263892;
  unsigned budget = 27;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
