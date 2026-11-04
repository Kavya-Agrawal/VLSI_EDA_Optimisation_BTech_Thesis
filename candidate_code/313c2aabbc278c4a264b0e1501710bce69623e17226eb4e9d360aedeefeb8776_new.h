// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54958483;
  double density_weight = 0.28209308;
  double prefix_weight = 0.31158751;
  double neighborhood_weight = 0.36091294;
  double late_weight = 0.19704236;
  double critical_weight = 0.15033561;
  unsigned budget = 35;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
