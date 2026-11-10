// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16309580;
  double density_weight = 0.36443172;
  double prefix_weight = 0.46634064;
  double neighborhood_weight = 0.30581631;
  double late_weight = 0.23230305;
  double critical_weight = 0.39134269;
  unsigned budget = 34;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
