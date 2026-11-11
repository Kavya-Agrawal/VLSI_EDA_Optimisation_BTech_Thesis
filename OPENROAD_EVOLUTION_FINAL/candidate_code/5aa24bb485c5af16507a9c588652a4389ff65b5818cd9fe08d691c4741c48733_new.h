// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78730419;
  double density_weight = 0.06593310;
  double prefix_weight = 0.46922134;
  double neighborhood_weight = 0.34057161;
  double late_weight = 0.14455076;
  double critical_weight = 0.12245612;
  unsigned budget = 33;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
