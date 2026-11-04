// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93226742;
  double density_weight = 0.43271675;
  double prefix_weight = 0.48292020;
  double neighborhood_weight = 0.08401771;
  double late_weight = 0.11474726;
  double critical_weight = 0.17155589;
  unsigned budget = 39;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
