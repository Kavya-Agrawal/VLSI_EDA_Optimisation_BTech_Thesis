// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66935218;
  double density_weight = 0.39799648;
  double prefix_weight = 0.26732734;
  double neighborhood_weight = 0.21681025;
  double late_weight = 0.26548267;
  double critical_weight = 0.01795216;
  unsigned budget = 23;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
