// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48733036;
  double density_weight = 0.11586560;
  double prefix_weight = 0.13051232;
  double neighborhood_weight = 0.04686070;
  double late_weight = 0.21502511;
  double critical_weight = 0.21550444;
  unsigned budget = 9;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
