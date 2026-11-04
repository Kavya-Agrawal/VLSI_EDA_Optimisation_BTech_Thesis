// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52266945;
  double density_weight = 0.05093290;
  double prefix_weight = 0.05773256;
  double neighborhood_weight = 0.09275616;
  double late_weight = 0.16398390;
  double critical_weight = 0.32995375;
  unsigned budget = 9;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
