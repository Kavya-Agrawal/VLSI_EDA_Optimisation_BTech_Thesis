// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42928811;
  double density_weight = 0.58540192;
  double prefix_weight = 0.17290724;
  double neighborhood_weight = 0.21719974;
  double late_weight = 0.09852316;
  double critical_weight = 0.14340973;
  unsigned budget = 16;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
