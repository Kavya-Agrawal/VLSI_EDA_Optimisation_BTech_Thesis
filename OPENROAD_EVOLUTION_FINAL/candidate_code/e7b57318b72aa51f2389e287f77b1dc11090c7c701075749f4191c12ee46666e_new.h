// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36509091;
  double density_weight = 0.34931221;
  double prefix_weight = 0.33423128;
  double neighborhood_weight = 0.01679153;
  double late_weight = 0.10174304;
  double critical_weight = 0.07031879;
  unsigned budget = 35;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
