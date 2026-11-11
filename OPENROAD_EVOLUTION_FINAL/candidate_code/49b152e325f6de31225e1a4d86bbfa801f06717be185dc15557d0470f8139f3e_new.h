// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19709744;
  double density_weight = 0.13719792;
  double prefix_weight = 0.17248323;
  double neighborhood_weight = 0.37910840;
  double late_weight = 0.19768834;
  double critical_weight = 0.15492954;
  unsigned budget = 20;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
