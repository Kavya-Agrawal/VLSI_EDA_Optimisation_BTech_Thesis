// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96970884;
  double density_weight = 0.01065982;
  double prefix_weight = 0.04953727;
  double neighborhood_weight = 0.31256916;
  double late_weight = 0.14326398;
  double critical_weight = 0.03387001;
  unsigned budget = 39;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
