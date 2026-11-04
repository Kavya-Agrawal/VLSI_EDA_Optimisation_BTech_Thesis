// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07414486;
  double density_weight = 0.58377892;
  double prefix_weight = 0.04643937;
  double neighborhood_weight = 0.14394740;
  double late_weight = 0.04839636;
  double critical_weight = 0.46367439;
  unsigned budget = 9;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
