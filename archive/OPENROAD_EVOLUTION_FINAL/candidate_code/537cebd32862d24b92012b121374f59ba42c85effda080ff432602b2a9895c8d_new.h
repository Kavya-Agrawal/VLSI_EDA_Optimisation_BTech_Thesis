// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87537109;
  double density_weight = 0.13132728;
  double prefix_weight = 0.05333698;
  double neighborhood_weight = 0.23194872;
  double late_weight = 0.28381283;
  double critical_weight = 0.16773287;
  unsigned budget = 8;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
