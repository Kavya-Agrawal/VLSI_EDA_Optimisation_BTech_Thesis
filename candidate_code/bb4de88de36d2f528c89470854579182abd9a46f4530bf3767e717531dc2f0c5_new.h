// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17411499;
  double density_weight = 0.03948138;
  double prefix_weight = 0.47188258;
  double neighborhood_weight = 0.34745873;
  double late_weight = 0.09237436;
  double critical_weight = 0.35013327;
  unsigned budget = 7;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
