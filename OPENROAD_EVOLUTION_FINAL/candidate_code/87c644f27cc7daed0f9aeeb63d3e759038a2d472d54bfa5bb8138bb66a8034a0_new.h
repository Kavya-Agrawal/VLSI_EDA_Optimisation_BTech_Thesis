// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01450919;
  double density_weight = 0.21836276;
  double prefix_weight = 0.27598100;
  double neighborhood_weight = 0.04784369;
  double late_weight = 0.10139865;
  double critical_weight = 0.20739482;
  unsigned budget = 15;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
