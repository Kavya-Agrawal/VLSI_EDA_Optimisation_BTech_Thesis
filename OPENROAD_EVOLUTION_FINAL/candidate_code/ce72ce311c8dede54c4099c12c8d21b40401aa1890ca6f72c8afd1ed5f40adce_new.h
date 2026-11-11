// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70656453;
  double density_weight = 0.41863024;
  double prefix_weight = 0.00441984;
  double neighborhood_weight = 0.16078776;
  double late_weight = 0.28973510;
  double critical_weight = 0.05664523;
  unsigned budget = 20;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
