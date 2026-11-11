// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45834857;
  double density_weight = 0.08277421;
  double prefix_weight = 0.25013310;
  double neighborhood_weight = 0.04076486;
  double late_weight = 0.09971665;
  double critical_weight = 0.47262114;
  unsigned budget = 40;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
