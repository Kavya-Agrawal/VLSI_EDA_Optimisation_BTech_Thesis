// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64689910;
  double density_weight = 0.07099046;
  double prefix_weight = 0.17613705;
  double neighborhood_weight = 0.01926218;
  double late_weight = 0.00365789;
  double critical_weight = 0.07826327;
  unsigned budget = 18;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
