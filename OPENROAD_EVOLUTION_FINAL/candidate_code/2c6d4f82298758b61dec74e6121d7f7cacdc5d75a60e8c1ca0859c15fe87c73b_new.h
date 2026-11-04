// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61456885;
  double density_weight = 0.38206006;
  double prefix_weight = 0.40122544;
  double neighborhood_weight = 0.24846905;
  double late_weight = 0.24331986;
  double critical_weight = 0.02473265;
  unsigned budget = 28;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
