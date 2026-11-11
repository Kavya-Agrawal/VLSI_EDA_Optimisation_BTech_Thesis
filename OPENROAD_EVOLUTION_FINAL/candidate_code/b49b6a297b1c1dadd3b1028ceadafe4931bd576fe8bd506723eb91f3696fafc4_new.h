// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00103824;
  double density_weight = 0.53401777;
  double prefix_weight = 0.47718232;
  double neighborhood_weight = 0.10938953;
  double late_weight = 0.14725197;
  double critical_weight = 0.06954866;
  unsigned budget = 29;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
