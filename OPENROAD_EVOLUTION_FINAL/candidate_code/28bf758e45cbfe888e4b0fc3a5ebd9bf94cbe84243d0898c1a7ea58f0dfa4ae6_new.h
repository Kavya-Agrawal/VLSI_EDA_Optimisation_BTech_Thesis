// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23821961;
  double density_weight = 0.30796301;
  double prefix_weight = 0.31769998;
  double neighborhood_weight = 0.06689210;
  double late_weight = 0.08183765;
  double critical_weight = 0.24634354;
  unsigned budget = 39;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
