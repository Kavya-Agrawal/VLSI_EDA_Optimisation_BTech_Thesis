// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16809445;
  double density_weight = 0.47593326;
  double prefix_weight = 0.27334325;
  double neighborhood_weight = 0.16725479;
  double late_weight = 0.02077776;
  double critical_weight = 0.35144045;
  unsigned budget = 6;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
