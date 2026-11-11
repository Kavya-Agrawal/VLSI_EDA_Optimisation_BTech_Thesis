// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81559653;
  double density_weight = 0.58267485;
  double prefix_weight = 0.35857092;
  double neighborhood_weight = 0.10907661;
  double late_weight = 0.26698808;
  double critical_weight = 0.27012473;
  unsigned budget = 13;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
