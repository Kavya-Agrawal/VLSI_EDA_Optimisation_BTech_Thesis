// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96253537;
  double density_weight = 0.14912829;
  double prefix_weight = 0.35990345;
  double neighborhood_weight = 0.14168375;
  double late_weight = 0.06509686;
  double critical_weight = 0.38627038;
  unsigned budget = 28;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
