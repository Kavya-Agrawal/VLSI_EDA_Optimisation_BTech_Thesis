// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59337769;
  double density_weight = 0.57899148;
  double prefix_weight = 0.29802307;
  double neighborhood_weight = 0.31028342;
  double late_weight = 0.02176103;
  double critical_weight = 0.22036030;
  unsigned budget = 8;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
