// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16254679;
  double density_weight = 0.47713386;
  double prefix_weight = 0.30446460;
  double neighborhood_weight = 0.23902129;
  double late_weight = 0.04019058;
  double critical_weight = 0.03739734;
  unsigned budget = 16;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
