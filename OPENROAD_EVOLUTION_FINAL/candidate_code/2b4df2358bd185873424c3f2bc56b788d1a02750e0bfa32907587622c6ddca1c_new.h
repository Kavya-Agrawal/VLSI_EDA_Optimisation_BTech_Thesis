// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35829546;
  double density_weight = 0.37089460;
  double prefix_weight = 0.08611465;
  double neighborhood_weight = 0.22641643;
  double late_weight = 0.27139240;
  double critical_weight = 0.36890210;
  unsigned budget = 6;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
