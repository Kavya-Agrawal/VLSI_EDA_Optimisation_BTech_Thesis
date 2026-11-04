// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03144480;
  double density_weight = 0.51395681;
  double prefix_weight = 0.34652309;
  double neighborhood_weight = 0.33333992;
  double late_weight = 0.16885544;
  double critical_weight = 0.31908730;
  unsigned budget = 4;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
