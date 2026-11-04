// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14387406;
  double density_weight = 0.13897455;
  double prefix_weight = 0.46103864;
  double neighborhood_weight = 0.04832648;
  double late_weight = 0.06651635;
  double critical_weight = 0.02385470;
  unsigned budget = 34;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
