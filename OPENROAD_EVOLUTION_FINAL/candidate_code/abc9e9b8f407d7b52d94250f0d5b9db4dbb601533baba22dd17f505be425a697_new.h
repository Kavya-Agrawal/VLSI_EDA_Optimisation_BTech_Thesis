// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66937134;
  double density_weight = 0.11586805;
  double prefix_weight = 0.42692178;
  double neighborhood_weight = 0.01648802;
  double late_weight = 0.12664283;
  double critical_weight = 0.18001772;
  unsigned budget = 26;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
