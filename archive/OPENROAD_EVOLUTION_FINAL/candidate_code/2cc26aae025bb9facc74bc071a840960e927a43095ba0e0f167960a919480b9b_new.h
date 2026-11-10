// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34183672;
  double density_weight = 0.01094994;
  double prefix_weight = 0.22996270;
  double neighborhood_weight = 0.09896607;
  double late_weight = 0.12583018;
  double critical_weight = 0.03977966;
  unsigned budget = 16;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
