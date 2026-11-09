// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28173370;
  double density_weight = 0.27605684;
  double prefix_weight = 0.22125948;
  double neighborhood_weight = 0.01944181;
  double late_weight = 0.14104380;
  double critical_weight = 0.42217102;
  unsigned budget = 10;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
