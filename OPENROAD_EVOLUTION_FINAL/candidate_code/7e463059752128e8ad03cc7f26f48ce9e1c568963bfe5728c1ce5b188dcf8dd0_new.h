// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85244263;
  double density_weight = 0.06575709;
  double prefix_weight = 0.15047744;
  double neighborhood_weight = 0.36724548;
  double late_weight = 0.20284926;
  double critical_weight = 0.48214351;
  unsigned budget = 10;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
