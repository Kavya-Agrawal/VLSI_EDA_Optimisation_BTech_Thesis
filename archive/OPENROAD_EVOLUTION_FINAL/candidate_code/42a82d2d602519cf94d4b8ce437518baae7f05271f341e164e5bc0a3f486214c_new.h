// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39693932;
  double density_weight = 0.20087566;
  double prefix_weight = 0.32206047;
  double neighborhood_weight = 0.35841613;
  double late_weight = 0.18140108;
  double critical_weight = 0.13177368;
  unsigned budget = 20;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
