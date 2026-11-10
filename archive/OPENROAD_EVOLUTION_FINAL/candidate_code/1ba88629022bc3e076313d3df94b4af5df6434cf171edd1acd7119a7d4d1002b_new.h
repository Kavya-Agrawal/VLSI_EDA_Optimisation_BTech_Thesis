// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78266454;
  double density_weight = 0.47931190;
  double prefix_weight = 0.20447703;
  double neighborhood_weight = 0.25176559;
  double late_weight = 0.00918791;
  double critical_weight = 0.25709861;
  unsigned budget = 23;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
