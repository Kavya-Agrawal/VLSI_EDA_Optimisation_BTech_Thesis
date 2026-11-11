// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59764833;
  double density_weight = 0.02008598;
  double prefix_weight = 0.39307677;
  double neighborhood_weight = 0.18435695;
  double late_weight = 0.12823607;
  double critical_weight = 0.38392708;
  unsigned budget = 25;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
