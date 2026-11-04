// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42649210;
  double density_weight = 0.40538603;
  double prefix_weight = 0.48494050;
  double neighborhood_weight = 0.22587406;
  double late_weight = 0.06708730;
  double critical_weight = 0.05080561;
  unsigned budget = 10;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
