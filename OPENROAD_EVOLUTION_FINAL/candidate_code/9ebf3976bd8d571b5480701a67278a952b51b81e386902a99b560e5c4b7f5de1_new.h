// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13967825;
  double density_weight = 0.41473312;
  double prefix_weight = 0.33958304;
  double neighborhood_weight = 0.26757600;
  double late_weight = 0.12411116;
  double critical_weight = 0.27136933;
  unsigned budget = 21;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
