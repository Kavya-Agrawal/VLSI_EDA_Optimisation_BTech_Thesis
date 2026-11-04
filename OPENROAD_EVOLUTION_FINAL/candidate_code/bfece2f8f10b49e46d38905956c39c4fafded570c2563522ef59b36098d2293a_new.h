// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22001282;
  double density_weight = 0.56988524;
  double prefix_weight = 0.07304479;
  double neighborhood_weight = 0.28233397;
  double late_weight = 0.08837796;
  double critical_weight = 0.48819073;
  unsigned budget = 39;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
