// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12299273;
  double density_weight = 0.17471409;
  double prefix_weight = 0.19707125;
  double neighborhood_weight = 0.24232530;
  double late_weight = 0.25367119;
  double critical_weight = 0.09567568;
  unsigned budget = 11;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
