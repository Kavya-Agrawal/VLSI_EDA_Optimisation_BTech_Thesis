// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40962472;
  double density_weight = 0.51425433;
  double prefix_weight = 0.31855082;
  double neighborhood_weight = 0.32791076;
  double late_weight = 0.09532990;
  double critical_weight = 0.15501203;
  unsigned budget = 34;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
