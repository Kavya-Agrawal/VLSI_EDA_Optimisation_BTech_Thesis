// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74924922;
  double density_weight = 0.15041073;
  double prefix_weight = 0.11621171;
  double neighborhood_weight = 0.37256662;
  double late_weight = 0.28347994;
  double critical_weight = 0.18365912;
  unsigned budget = 39;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
