// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37170641;
  double density_weight = 0.59889833;
  double prefix_weight = 0.13506593;
  double neighborhood_weight = 0.26173236;
  double late_weight = 0.25891421;
  double critical_weight = 0.18520993;
  unsigned budget = 23;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
