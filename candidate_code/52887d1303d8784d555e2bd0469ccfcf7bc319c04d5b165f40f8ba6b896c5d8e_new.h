// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63642470;
  double density_weight = 0.16179928;
  double prefix_weight = 0.30740894;
  double neighborhood_weight = 0.33506813;
  double late_weight = 0.02969298;
  double critical_weight = 0.38433697;
  unsigned budget = 14;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
