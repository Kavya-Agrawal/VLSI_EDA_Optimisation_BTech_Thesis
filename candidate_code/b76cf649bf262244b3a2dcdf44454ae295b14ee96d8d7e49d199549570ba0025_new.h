// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89353249;
  double density_weight = 0.50548896;
  double prefix_weight = 0.25458284;
  double neighborhood_weight = 0.27139718;
  double late_weight = 0.06581530;
  double critical_weight = 0.47356069;
  unsigned budget = 13;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
