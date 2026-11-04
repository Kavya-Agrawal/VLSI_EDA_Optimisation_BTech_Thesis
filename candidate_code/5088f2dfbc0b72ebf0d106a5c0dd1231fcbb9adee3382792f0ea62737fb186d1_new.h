// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72112848;
  double density_weight = 0.54506865;
  double prefix_weight = 0.49116675;
  double neighborhood_weight = 0.29003504;
  double late_weight = 0.24787156;
  double critical_weight = 0.11456984;
  unsigned budget = 5;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
