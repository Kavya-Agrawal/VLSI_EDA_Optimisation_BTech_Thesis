// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60537023;
  double density_weight = 0.40899234;
  double prefix_weight = 0.28726261;
  double neighborhood_weight = 0.35240170;
  double late_weight = 0.14251371;
  double critical_weight = 0.33268709;
  unsigned budget = 40;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
