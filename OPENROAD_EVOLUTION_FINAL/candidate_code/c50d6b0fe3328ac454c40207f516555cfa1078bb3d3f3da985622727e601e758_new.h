// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21337585;
  double density_weight = 0.45609095;
  double prefix_weight = 0.04880830;
  double neighborhood_weight = 0.01621022;
  double late_weight = 0.23699968;
  double critical_weight = 0.20054887;
  unsigned budget = 31;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
