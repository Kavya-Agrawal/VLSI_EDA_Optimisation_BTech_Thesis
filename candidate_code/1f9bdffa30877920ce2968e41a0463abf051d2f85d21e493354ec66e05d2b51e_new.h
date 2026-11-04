// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93112616;
  double density_weight = 0.42396863;
  double prefix_weight = 0.37347314;
  double neighborhood_weight = 0.34796501;
  double late_weight = 0.28004547;
  double critical_weight = 0.14523208;
  unsigned budget = 12;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
