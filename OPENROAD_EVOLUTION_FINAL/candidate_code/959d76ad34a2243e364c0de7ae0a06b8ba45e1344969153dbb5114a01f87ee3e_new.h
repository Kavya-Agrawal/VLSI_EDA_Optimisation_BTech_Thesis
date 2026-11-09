// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62072097;
  double density_weight = 0.53481048;
  double prefix_weight = 0.41969286;
  double neighborhood_weight = 0.16633509;
  double late_weight = 0.29154933;
  double critical_weight = 0.19172993;
  unsigned budget = 33;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
