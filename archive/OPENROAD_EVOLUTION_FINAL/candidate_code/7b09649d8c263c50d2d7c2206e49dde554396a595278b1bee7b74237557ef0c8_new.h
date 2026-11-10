// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01482228;
  double density_weight = 0.00119247;
  double prefix_weight = 0.36142282;
  double neighborhood_weight = 0.13077776;
  double late_weight = 0.28367412;
  double critical_weight = 0.01114378;
  unsigned budget = 16;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
