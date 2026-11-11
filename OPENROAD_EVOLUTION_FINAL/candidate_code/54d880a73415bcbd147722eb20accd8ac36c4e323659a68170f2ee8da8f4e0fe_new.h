// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03677161;
  double density_weight = 0.16830391;
  double prefix_weight = 0.26937215;
  double neighborhood_weight = 0.13463002;
  double late_weight = 0.05049772;
  double critical_weight = 0.07154339;
  unsigned budget = 6;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
