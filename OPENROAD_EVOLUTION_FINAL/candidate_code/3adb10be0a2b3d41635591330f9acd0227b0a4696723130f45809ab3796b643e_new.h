// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43207046;
  double density_weight = 0.07950409;
  double prefix_weight = 0.45299011;
  double neighborhood_weight = 0.10407546;
  double late_weight = 0.26223024;
  double critical_weight = 0.19485598;
  unsigned budget = 11;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
