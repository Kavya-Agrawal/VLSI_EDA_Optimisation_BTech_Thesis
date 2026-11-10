// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63262660;
  double density_weight = 0.20092058;
  double prefix_weight = 0.35190428;
  double neighborhood_weight = 0.21341739;
  double late_weight = 0.00262491;
  double critical_weight = 0.40357507;
  unsigned budget = 4;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
