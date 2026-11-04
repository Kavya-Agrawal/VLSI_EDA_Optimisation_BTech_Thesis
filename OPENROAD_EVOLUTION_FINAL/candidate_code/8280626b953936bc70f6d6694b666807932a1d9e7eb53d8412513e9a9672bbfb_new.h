// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89664536;
  double density_weight = 0.04011720;
  double prefix_weight = 0.46291762;
  double neighborhood_weight = 0.12624787;
  double late_weight = 0.23012836;
  double critical_weight = 0.19832199;
  unsigned budget = 36;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
