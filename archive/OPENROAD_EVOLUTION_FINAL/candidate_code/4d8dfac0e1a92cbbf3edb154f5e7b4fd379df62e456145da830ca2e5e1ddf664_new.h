// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72542603;
  double density_weight = 0.17845283;
  double prefix_weight = 0.02147072;
  double neighborhood_weight = 0.38655124;
  double late_weight = 0.08568899;
  double critical_weight = 0.37591724;
  unsigned budget = 14;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
