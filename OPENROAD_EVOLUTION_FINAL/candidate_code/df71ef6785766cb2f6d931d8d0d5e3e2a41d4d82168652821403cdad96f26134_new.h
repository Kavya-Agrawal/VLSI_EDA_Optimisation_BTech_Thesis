// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76028151;
  double density_weight = 0.04320877;
  double prefix_weight = 0.10834450;
  double neighborhood_weight = 0.33330108;
  double late_weight = 0.16547369;
  double critical_weight = 0.29780964;
  unsigned budget = 5;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
