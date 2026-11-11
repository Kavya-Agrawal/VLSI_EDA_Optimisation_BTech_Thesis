// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00104949;
  double density_weight = 0.38871238;
  double prefix_weight = 0.25252091;
  double neighborhood_weight = 0.02613829;
  double late_weight = 0.26651168;
  double critical_weight = 0.37947306;
  unsigned budget = 39;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
