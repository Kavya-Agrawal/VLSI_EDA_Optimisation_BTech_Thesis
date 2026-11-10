// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70347178;
  double density_weight = 0.16423399;
  double prefix_weight = 0.09579456;
  double neighborhood_weight = 0.07286405;
  double late_weight = 0.28434878;
  double critical_weight = 0.36795934;
  unsigned budget = 8;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
