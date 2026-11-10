// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95901622;
  double density_weight = 0.01677102;
  double prefix_weight = 0.41849567;
  double neighborhood_weight = 0.09997427;
  double late_weight = 0.19900259;
  double critical_weight = 0.24104502;
  unsigned budget = 6;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
