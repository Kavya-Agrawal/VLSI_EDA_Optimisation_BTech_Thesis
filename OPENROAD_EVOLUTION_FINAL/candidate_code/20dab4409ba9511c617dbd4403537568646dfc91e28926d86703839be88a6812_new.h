// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24380965;
  double density_weight = 0.52413462;
  double prefix_weight = 0.42463582;
  double neighborhood_weight = 0.31492034;
  double late_weight = 0.17025725;
  double critical_weight = 0.18245621;
  unsigned budget = 18;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
