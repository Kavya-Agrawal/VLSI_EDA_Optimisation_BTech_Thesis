// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64037157;
  double density_weight = 0.45337311;
  double prefix_weight = 0.42008002;
  double neighborhood_weight = 0.08559467;
  double late_weight = 0.13361003;
  double critical_weight = 0.28638055;
  unsigned budget = 23;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
