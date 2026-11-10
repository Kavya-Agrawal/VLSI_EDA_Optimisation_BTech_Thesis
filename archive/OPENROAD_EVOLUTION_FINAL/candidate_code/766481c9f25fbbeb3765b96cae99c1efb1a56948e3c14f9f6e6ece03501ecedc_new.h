// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14108509;
  double density_weight = 0.18517951;
  double prefix_weight = 0.28902660;
  double neighborhood_weight = 0.13702525;
  double late_weight = 0.00908943;
  double critical_weight = 0.34450073;
  unsigned budget = 7;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
