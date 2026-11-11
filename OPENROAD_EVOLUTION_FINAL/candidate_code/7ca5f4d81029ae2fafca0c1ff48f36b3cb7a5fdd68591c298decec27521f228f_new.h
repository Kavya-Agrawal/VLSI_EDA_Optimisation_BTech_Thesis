// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17622900;
  double density_weight = 0.14351811;
  double prefix_weight = 0.37983240;
  double neighborhood_weight = 0.33559040;
  double late_weight = 0.24052805;
  double critical_weight = 0.21973589;
  unsigned budget = 34;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
