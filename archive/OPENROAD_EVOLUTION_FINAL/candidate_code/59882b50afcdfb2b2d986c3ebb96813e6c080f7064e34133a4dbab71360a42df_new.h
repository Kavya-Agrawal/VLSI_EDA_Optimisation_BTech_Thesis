// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77810253;
  double density_weight = 0.43814094;
  double prefix_weight = 0.33422097;
  double neighborhood_weight = 0.39183773;
  double late_weight = 0.16611270;
  double critical_weight = 0.22609898;
  unsigned budget = 13;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
