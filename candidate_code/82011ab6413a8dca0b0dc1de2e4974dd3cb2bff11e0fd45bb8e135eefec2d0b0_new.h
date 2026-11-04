// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37772395;
  double density_weight = 0.52095066;
  double prefix_weight = 0.43366046;
  double neighborhood_weight = 0.24986375;
  double late_weight = 0.06854104;
  double critical_weight = 0.11377132;
  unsigned budget = 35;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
