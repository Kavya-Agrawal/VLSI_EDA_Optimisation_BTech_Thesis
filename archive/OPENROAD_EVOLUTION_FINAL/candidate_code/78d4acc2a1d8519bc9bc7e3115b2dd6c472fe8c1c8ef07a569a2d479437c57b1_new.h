// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25771643;
  double density_weight = 0.54777579;
  double prefix_weight = 0.42257530;
  double neighborhood_weight = 0.01182987;
  double late_weight = 0.29635300;
  double critical_weight = 0.18247102;
  unsigned budget = 25;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
