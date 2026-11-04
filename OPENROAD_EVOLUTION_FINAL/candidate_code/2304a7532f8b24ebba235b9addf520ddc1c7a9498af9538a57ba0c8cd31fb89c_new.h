// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27791614;
  double density_weight = 0.41560032;
  double prefix_weight = 0.01579027;
  double neighborhood_weight = 0.17188793;
  double late_weight = 0.27093470;
  double critical_weight = 0.49685760;
  unsigned budget = 23;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
