// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42982537;
  double density_weight = 0.28184081;
  double prefix_weight = 0.01150006;
  double neighborhood_weight = 0.30504376;
  double late_weight = 0.13930571;
  double critical_weight = 0.40446462;
  unsigned budget = 11;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
