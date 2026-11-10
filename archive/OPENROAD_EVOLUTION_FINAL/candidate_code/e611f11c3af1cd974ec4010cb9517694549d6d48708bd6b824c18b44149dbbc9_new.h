// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98842098;
  double density_weight = 0.30566727;
  double prefix_weight = 0.44072597;
  double neighborhood_weight = 0.22396886;
  double late_weight = 0.10619711;
  double critical_weight = 0.23314493;
  unsigned budget = 13;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
