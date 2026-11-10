// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75073797;
  double density_weight = 0.00482860;
  double prefix_weight = 0.35809864;
  double neighborhood_weight = 0.08389309;
  double late_weight = 0.15885204;
  double critical_weight = 0.47568502;
  unsigned budget = 33;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
