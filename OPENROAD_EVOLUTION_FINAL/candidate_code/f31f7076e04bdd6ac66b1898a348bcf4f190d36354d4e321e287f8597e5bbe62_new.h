// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89249107;
  double density_weight = 0.50210697;
  double prefix_weight = 0.15018983;
  double neighborhood_weight = 0.00645554;
  double late_weight = 0.21511031;
  double critical_weight = 0.26902687;
  unsigned budget = 7;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
