// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93677597;
  double density_weight = 0.39247884;
  double prefix_weight = 0.08028762;
  double neighborhood_weight = 0.28829264;
  double late_weight = 0.03422190;
  double critical_weight = 0.35126452;
  unsigned budget = 38;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
