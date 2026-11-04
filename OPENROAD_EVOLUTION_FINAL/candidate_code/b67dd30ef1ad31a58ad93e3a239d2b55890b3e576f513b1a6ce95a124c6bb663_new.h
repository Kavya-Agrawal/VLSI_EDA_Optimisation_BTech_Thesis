// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97394419;
  double density_weight = 0.52476331;
  double prefix_weight = 0.46316335;
  double neighborhood_weight = 0.13120495;
  double late_weight = 0.00056229;
  double critical_weight = 0.21272108;
  unsigned budget = 9;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
