// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38929073;
  double density_weight = 0.37215406;
  double prefix_weight = 0.18877964;
  double neighborhood_weight = 0.13225713;
  double late_weight = 0.08972189;
  double critical_weight = 0.26523642;
  unsigned budget = 15;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
