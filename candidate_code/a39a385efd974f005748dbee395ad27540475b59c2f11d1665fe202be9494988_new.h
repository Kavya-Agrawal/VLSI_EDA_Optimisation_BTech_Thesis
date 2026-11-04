// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54030334;
  double density_weight = 0.36767201;
  double prefix_weight = 0.20157034;
  double neighborhood_weight = 0.11625599;
  double late_weight = 0.14663485;
  double critical_weight = 0.31441072;
  unsigned budget = 15;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
