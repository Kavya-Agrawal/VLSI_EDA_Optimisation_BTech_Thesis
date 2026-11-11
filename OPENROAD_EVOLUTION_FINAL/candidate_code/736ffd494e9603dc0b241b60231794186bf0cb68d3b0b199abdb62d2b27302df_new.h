// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75864395;
  double density_weight = 0.22184037;
  double prefix_weight = 0.23319969;
  double neighborhood_weight = 0.32364903;
  double late_weight = 0.04949486;
  double critical_weight = 0.04649923;
  unsigned budget = 35;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
