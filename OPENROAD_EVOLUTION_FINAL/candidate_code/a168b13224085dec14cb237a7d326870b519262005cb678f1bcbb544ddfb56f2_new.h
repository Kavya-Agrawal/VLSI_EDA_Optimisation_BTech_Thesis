// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51337909;
  double density_weight = 0.20404373;
  double prefix_weight = 0.34892015;
  double neighborhood_weight = 0.23376973;
  double late_weight = 0.00254062;
  double critical_weight = 0.15271061;
  unsigned budget = 33;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
