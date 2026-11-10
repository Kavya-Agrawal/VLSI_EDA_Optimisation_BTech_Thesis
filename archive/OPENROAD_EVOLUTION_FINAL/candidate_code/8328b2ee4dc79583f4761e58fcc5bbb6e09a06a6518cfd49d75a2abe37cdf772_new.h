// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94836710;
  double density_weight = 0.33583217;
  double prefix_weight = 0.31419054;
  double neighborhood_weight = 0.31421793;
  double late_weight = 0.15421274;
  double critical_weight = 0.38070876;
  unsigned budget = 30;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
