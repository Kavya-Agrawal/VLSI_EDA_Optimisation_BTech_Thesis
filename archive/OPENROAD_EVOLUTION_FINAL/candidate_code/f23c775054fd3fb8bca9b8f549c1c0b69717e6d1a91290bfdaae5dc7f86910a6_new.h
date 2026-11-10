// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03083671;
  double density_weight = 0.53827907;
  double prefix_weight = 0.09599180;
  double neighborhood_weight = 0.28006958;
  double late_weight = 0.14242577;
  double critical_weight = 0.15081544;
  unsigned budget = 39;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
