// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54723260;
  double density_weight = 0.02007561;
  double prefix_weight = 0.48490592;
  double neighborhood_weight = 0.34529138;
  double late_weight = 0.07859067;
  double critical_weight = 0.45419227;
  unsigned budget = 35;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
