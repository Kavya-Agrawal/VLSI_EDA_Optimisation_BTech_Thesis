// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55798616;
  double density_weight = 0.45401292;
  double prefix_weight = 0.27257824;
  double neighborhood_weight = 0.09030728;
  double late_weight = 0.05630061;
  double critical_weight = 0.44359170;
  unsigned budget = 18;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
