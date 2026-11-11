// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34474008;
  double density_weight = 0.10675950;
  double prefix_weight = 0.15302282;
  double neighborhood_weight = 0.22224919;
  double late_weight = 0.03149048;
  double critical_weight = 0.08695212;
  unsigned budget = 19;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
