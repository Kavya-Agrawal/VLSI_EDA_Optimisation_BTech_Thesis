// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06837069;
  double density_weight = 0.51879948;
  double prefix_weight = 0.09124357;
  double neighborhood_weight = 0.03985475;
  double late_weight = 0.07438895;
  double critical_weight = 0.48330627;
  unsigned budget = 32;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
