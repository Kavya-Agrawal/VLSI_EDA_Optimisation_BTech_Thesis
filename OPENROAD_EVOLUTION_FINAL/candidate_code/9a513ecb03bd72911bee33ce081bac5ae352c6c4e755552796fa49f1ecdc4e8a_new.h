// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19780198;
  double density_weight = 0.04496713;
  double prefix_weight = 0.49833352;
  double neighborhood_weight = 0.26727244;
  double late_weight = 0.24690395;
  double critical_weight = 0.12557062;
  unsigned budget = 39;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
