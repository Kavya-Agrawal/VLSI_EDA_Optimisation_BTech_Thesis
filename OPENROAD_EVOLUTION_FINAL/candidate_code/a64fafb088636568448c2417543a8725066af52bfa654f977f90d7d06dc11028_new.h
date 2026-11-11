// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72906805;
  double density_weight = 0.44341316;
  double prefix_weight = 0.02105192;
  double neighborhood_weight = 0.39171594;
  double late_weight = 0.15778971;
  double critical_weight = 0.03338794;
  unsigned budget = 22;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
