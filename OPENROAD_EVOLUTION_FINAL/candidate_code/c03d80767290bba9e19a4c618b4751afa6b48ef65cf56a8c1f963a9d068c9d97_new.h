// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67016424;
  double density_weight = 0.41973166;
  double prefix_weight = 0.36223024;
  double neighborhood_weight = 0.08081043;
  double late_weight = 0.29078454;
  double critical_weight = 0.31746764;
  unsigned budget = 30;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
