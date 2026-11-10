// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96097869;
  double density_weight = 0.37362294;
  double prefix_weight = 0.09953316;
  double neighborhood_weight = 0.20554796;
  double late_weight = 0.04260746;
  double critical_weight = 0.37893959;
  unsigned budget = 34;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
