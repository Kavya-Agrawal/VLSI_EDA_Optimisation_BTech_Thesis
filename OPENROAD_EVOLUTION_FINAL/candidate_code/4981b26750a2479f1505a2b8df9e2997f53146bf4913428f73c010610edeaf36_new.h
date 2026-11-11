// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31940024;
  double density_weight = 0.30945589;
  double prefix_weight = 0.30667871;
  double neighborhood_weight = 0.14886663;
  double late_weight = 0.13990372;
  double critical_weight = 0.06950109;
  unsigned budget = 25;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
