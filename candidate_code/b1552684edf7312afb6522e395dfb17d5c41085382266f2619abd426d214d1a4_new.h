// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56748613;
  double density_weight = 0.59099982;
  double prefix_weight = 0.19720918;
  double neighborhood_weight = 0.05318331;
  double late_weight = 0.29140070;
  double critical_weight = 0.17253469;
  unsigned budget = 8;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
