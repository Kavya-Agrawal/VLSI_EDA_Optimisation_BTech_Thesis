// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63927299;
  double density_weight = 0.10004148;
  double prefix_weight = 0.11123080;
  double neighborhood_weight = 0.13494115;
  double late_weight = 0.01302286;
  double critical_weight = 0.07720599;
  unsigned budget = 22;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
