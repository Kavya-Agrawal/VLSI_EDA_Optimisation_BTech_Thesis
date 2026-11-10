// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07293997;
  double density_weight = 0.08828752;
  double prefix_weight = 0.29924919;
  double neighborhood_weight = 0.14743912;
  double late_weight = 0.23893022;
  double critical_weight = 0.36285568;
  unsigned budget = 13;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
