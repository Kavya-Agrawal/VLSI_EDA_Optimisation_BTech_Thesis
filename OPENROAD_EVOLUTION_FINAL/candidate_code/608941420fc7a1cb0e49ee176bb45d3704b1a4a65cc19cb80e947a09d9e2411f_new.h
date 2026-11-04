// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99746429;
  double density_weight = 0.39145054;
  double prefix_weight = 0.24426281;
  double neighborhood_weight = 0.10815497;
  double late_weight = 0.29252236;
  double critical_weight = 0.28987100;
  unsigned budget = 15;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
