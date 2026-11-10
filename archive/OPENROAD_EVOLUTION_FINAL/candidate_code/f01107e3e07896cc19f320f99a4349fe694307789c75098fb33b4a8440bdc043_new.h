// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41888485;
  double density_weight = 0.02720472;
  double prefix_weight = 0.11425447;
  double neighborhood_weight = 0.33551793;
  double late_weight = 0.04871351;
  double critical_weight = 0.07555400;
  unsigned budget = 35;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
