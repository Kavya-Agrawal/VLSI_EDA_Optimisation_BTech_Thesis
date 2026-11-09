// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53211767;
  double density_weight = 0.22848296;
  double prefix_weight = 0.33394473;
  double neighborhood_weight = 0.25109914;
  double late_weight = 0.01354935;
  double critical_weight = 0.30085479;
  unsigned budget = 9;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
