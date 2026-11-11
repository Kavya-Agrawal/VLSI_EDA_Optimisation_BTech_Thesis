// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25413376;
  double density_weight = 0.42860510;
  double prefix_weight = 0.28222931;
  double neighborhood_weight = 0.29214097;
  double late_weight = 0.11729373;
  double critical_weight = 0.21197901;
  unsigned budget = 26;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
