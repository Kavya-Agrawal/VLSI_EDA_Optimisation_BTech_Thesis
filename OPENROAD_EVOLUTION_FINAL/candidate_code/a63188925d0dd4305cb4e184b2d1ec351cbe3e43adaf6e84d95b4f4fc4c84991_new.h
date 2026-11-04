// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41419958;
  double density_weight = 0.38833387;
  double prefix_weight = 0.16829508;
  double neighborhood_weight = 0.05453350;
  double late_weight = 0.16633575;
  double critical_weight = 0.39582313;
  unsigned budget = 36;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
