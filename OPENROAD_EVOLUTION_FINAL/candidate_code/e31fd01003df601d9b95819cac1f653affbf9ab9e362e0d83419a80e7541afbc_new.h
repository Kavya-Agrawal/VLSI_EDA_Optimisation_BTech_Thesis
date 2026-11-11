// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16205256;
  double density_weight = 0.48638358;
  double prefix_weight = 0.34364641;
  double neighborhood_weight = 0.00711355;
  double late_weight = 0.28271375;
  double critical_weight = 0.47155297;
  unsigned budget = 23;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
