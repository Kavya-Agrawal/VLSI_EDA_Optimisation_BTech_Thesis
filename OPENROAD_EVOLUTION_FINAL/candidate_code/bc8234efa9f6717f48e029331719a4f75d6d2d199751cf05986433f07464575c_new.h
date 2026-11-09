// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22559378;
  double density_weight = 0.38336871;
  double prefix_weight = 0.20027669;
  double neighborhood_weight = 0.13582744;
  double late_weight = 0.03975865;
  double critical_weight = 0.27611666;
  unsigned budget = 40;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
