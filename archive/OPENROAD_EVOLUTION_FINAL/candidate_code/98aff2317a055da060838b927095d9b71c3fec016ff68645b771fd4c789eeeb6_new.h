// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61052042;
  double density_weight = 0.35269389;
  double prefix_weight = 0.46125422;
  double neighborhood_weight = 0.15994100;
  double late_weight = 0.08081715;
  double critical_weight = 0.15384314;
  unsigned budget = 39;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
