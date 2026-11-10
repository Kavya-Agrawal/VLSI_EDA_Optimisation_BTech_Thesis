// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47540551;
  double density_weight = 0.28927566;
  double prefix_weight = 0.39534660;
  double neighborhood_weight = 0.07463046;
  double late_weight = 0.05749321;
  double critical_weight = 0.06191258;
  unsigned budget = 15;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
