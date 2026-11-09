// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41543315;
  double density_weight = 0.43291141;
  double prefix_weight = 0.09765982;
  double neighborhood_weight = 0.00119108;
  double late_weight = 0.22927076;
  double critical_weight = 0.09460638;
  unsigned budget = 34;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
