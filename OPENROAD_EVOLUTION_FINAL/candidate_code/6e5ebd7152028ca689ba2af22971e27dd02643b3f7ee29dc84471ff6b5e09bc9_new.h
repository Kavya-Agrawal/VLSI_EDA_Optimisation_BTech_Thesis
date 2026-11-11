// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80699980;
  double density_weight = 0.23587885;
  double prefix_weight = 0.20269437;
  double neighborhood_weight = 0.03566710;
  double late_weight = 0.16381638;
  double critical_weight = 0.33837354;
  unsigned budget = 21;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
