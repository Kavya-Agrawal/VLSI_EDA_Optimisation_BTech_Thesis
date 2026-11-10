// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21778368;
  double density_weight = 0.07200696;
  double prefix_weight = 0.30253903;
  double neighborhood_weight = 0.33227571;
  double late_weight = 0.07963391;
  double critical_weight = 0.24907089;
  unsigned budget = 5;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
