// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27795395;
  double density_weight = 0.19821917;
  double prefix_weight = 0.11543815;
  double neighborhood_weight = 0.30006308;
  double late_weight = 0.19966044;
  double critical_weight = 0.31156361;
  unsigned budget = 39;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
