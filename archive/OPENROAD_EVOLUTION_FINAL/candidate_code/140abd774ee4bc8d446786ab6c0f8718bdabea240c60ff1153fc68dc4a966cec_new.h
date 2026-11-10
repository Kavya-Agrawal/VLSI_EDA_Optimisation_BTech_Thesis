// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63711170;
  double density_weight = 0.32268129;
  double prefix_weight = 0.40259369;
  double neighborhood_weight = 0.32189362;
  double late_weight = 0.10182350;
  double critical_weight = 0.03135825;
  unsigned budget = 22;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
