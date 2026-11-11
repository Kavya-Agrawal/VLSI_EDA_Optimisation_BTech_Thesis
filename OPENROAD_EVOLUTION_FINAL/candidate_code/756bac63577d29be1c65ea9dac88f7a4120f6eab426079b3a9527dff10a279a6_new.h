// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00178750;
  double density_weight = 0.38457283;
  double prefix_weight = 0.24278884;
  double neighborhood_weight = 0.07288604;
  double late_weight = 0.05066494;
  double critical_weight = 0.35513843;
  unsigned budget = 26;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
