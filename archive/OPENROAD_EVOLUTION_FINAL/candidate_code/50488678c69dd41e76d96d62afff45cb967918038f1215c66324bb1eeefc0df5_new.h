// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26965812;
  double density_weight = 0.27846364;
  double prefix_weight = 0.39061640;
  double neighborhood_weight = 0.31573888;
  double late_weight = 0.12019614;
  double critical_weight = 0.09667090;
  unsigned budget = 28;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
