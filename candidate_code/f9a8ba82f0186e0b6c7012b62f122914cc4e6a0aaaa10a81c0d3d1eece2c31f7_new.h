// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32984908;
  double density_weight = 0.42315142;
  double prefix_weight = 0.15607563;
  double neighborhood_weight = 0.03414270;
  double late_weight = 0.25357503;
  double critical_weight = 0.11183473;
  unsigned budget = 37;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
