// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44141488;
  double density_weight = 0.07409490;
  double prefix_weight = 0.13680810;
  double neighborhood_weight = 0.08764858;
  double late_weight = 0.08051836;
  double critical_weight = 0.43505002;
  unsigned budget = 12;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
