// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38725222;
  double density_weight = 0.38402623;
  double prefix_weight = 0.47027357;
  double neighborhood_weight = 0.32589942;
  double late_weight = 0.19661547;
  double critical_weight = 0.00655610;
  unsigned budget = 20;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
