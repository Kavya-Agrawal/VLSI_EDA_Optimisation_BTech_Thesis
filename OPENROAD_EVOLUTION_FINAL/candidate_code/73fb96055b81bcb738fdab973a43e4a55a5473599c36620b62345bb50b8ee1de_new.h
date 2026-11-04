// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76713818;
  double density_weight = 0.06133349;
  double prefix_weight = 0.38408358;
  double neighborhood_weight = 0.25447316;
  double late_weight = 0.18551230;
  double critical_weight = 0.15164626;
  unsigned budget = 13;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
