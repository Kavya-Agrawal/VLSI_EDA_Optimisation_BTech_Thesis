// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26211711;
  double density_weight = 0.25277517;
  double prefix_weight = 0.48256865;
  double neighborhood_weight = 0.39092805;
  double late_weight = 0.16631201;
  double critical_weight = 0.19907182;
  unsigned budget = 38;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
