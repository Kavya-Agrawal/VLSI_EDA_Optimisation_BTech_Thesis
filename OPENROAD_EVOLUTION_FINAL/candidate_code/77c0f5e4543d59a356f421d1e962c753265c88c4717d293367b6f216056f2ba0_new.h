// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42533303;
  double density_weight = 0.55222392;
  double prefix_weight = 0.36179897;
  double neighborhood_weight = 0.31862799;
  double late_weight = 0.05650142;
  double critical_weight = 0.47154506;
  unsigned budget = 25;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
