// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07222946;
  double density_weight = 0.46690003;
  double prefix_weight = 0.14126884;
  double neighborhood_weight = 0.05275288;
  double late_weight = 0.24317413;
  double critical_weight = 0.25531973;
  unsigned budget = 23;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
