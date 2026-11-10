// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84538541;
  double density_weight = 0.38043942;
  double prefix_weight = 0.30123246;
  double neighborhood_weight = 0.14069299;
  double late_weight = 0.15896884;
  double critical_weight = 0.02219703;
  unsigned budget = 40;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
