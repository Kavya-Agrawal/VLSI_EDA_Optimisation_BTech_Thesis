// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39048382;
  double density_weight = 0.16153195;
  double prefix_weight = 0.22934944;
  double neighborhood_weight = 0.11961590;
  double late_weight = 0.28746782;
  double critical_weight = 0.30424897;
  unsigned budget = 5;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
