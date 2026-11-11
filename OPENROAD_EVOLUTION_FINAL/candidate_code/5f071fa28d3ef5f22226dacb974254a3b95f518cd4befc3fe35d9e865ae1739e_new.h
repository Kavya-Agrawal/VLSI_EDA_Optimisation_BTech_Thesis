// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17727796;
  double density_weight = 0.42776776;
  double prefix_weight = 0.14661080;
  double neighborhood_weight = 0.39611547;
  double late_weight = 0.05914699;
  double critical_weight = 0.16970118;
  unsigned budget = 31;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
