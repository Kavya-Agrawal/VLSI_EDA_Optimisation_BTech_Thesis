// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86431263;
  double density_weight = 0.00990805;
  double prefix_weight = 0.27267537;
  double neighborhood_weight = 0.07571775;
  double late_weight = 0.17506733;
  double critical_weight = 0.31519905;
  unsigned budget = 10;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
