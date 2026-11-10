// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21479935;
  double density_weight = 0.42021439;
  double prefix_weight = 0.44631404;
  double neighborhood_weight = 0.37931488;
  double late_weight = 0.18650695;
  double critical_weight = 0.27921772;
  unsigned budget = 33;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
