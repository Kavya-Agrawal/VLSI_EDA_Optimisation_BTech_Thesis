// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74719955;
  double density_weight = 0.01856395;
  double prefix_weight = 0.25563054;
  double neighborhood_weight = 0.07440122;
  double late_weight = 0.03336402;
  double critical_weight = 0.45353608;
  unsigned budget = 4;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
