// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20704728;
  double density_weight = 0.18587532;
  double prefix_weight = 0.20213399;
  double neighborhood_weight = 0.32128222;
  double late_weight = 0.17861641;
  double critical_weight = 0.13667123;
  unsigned budget = 25;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
