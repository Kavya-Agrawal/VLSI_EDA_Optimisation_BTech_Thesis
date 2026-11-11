// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01701312;
  double density_weight = 0.24793323;
  double prefix_weight = 0.48730123;
  double neighborhood_weight = 0.21743901;
  double late_weight = 0.28125011;
  double critical_weight = 0.27566675;
  unsigned budget = 24;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
