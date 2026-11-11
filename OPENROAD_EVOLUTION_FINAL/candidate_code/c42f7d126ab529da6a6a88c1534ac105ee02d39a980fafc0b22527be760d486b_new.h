// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19100339;
  double density_weight = 0.49641067;
  double prefix_weight = 0.04464601;
  double neighborhood_weight = 0.22717392;
  double late_weight = 0.11170756;
  double critical_weight = 0.48940212;
  unsigned budget = 37;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
