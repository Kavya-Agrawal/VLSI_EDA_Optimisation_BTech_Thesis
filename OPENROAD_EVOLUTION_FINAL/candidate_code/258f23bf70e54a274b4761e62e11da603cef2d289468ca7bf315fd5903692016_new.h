// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23536757;
  double density_weight = 0.37131163;
  double prefix_weight = 0.26625565;
  double neighborhood_weight = 0.06280877;
  double late_weight = 0.04475637;
  double critical_weight = 0.34695925;
  unsigned budget = 39;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
