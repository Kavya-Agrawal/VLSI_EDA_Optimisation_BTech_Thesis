// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46826944;
  double density_weight = 0.29707406;
  double prefix_weight = 0.48540191;
  double neighborhood_weight = 0.35027633;
  double late_weight = 0.01219424;
  double critical_weight = 0.02004006;
  unsigned budget = 18;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
