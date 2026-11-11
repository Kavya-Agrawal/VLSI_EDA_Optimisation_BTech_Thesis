// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56329710;
  double density_weight = 0.47916514;
  double prefix_weight = 0.18778401;
  double neighborhood_weight = 0.14742485;
  double late_weight = 0.00137638;
  double critical_weight = 0.00144326;
  unsigned budget = 37;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
