// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49623538;
  double density_weight = 0.16481670;
  double prefix_weight = 0.19210542;
  double neighborhood_weight = 0.05918304;
  double late_weight = 0.11783736;
  double critical_weight = 0.19135554;
  unsigned budget = 10;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
