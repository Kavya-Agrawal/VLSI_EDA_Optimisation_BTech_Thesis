// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07164417;
  double density_weight = 0.04442202;
  double prefix_weight = 0.31005210;
  double neighborhood_weight = 0.29250716;
  double late_weight = 0.27314635;
  double critical_weight = 0.13649663;
  unsigned budget = 31;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
