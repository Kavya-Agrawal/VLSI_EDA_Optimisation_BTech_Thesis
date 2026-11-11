// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04340850;
  double density_weight = 0.11722713;
  double prefix_weight = 0.22015374;
  double neighborhood_weight = 0.26762523;
  double late_weight = 0.12341269;
  double critical_weight = 0.00032650;
  unsigned budget = 24;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
