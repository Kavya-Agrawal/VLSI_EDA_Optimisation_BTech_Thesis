// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25264263;
  double density_weight = 0.35355908;
  double prefix_weight = 0.16577566;
  double neighborhood_weight = 0.33106929;
  double late_weight = 0.24821451;
  double critical_weight = 0.35875853;
  unsigned budget = 36;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
