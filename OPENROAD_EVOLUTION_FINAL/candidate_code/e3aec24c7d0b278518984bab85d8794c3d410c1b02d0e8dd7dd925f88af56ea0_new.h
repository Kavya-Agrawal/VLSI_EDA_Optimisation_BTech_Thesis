// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59666880;
  double density_weight = 0.48398186;
  double prefix_weight = 0.25130753;
  double neighborhood_weight = 0.38658655;
  double late_weight = 0.11391596;
  double critical_weight = 0.41197757;
  unsigned budget = 9;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
