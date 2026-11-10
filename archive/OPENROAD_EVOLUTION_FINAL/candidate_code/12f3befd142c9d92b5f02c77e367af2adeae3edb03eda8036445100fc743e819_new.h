// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85839723;
  double density_weight = 0.41021026;
  double prefix_weight = 0.36374986;
  double neighborhood_weight = 0.13188485;
  double late_weight = 0.23396988;
  double critical_weight = 0.07041519;
  unsigned budget = 16;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
