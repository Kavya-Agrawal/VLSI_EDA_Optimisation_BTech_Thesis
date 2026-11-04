// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04866915;
  double density_weight = 0.31813348;
  double prefix_weight = 0.43276138;
  double neighborhood_weight = 0.27371861;
  double late_weight = 0.13228358;
  double critical_weight = 0.26711692;
  unsigned budget = 15;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
