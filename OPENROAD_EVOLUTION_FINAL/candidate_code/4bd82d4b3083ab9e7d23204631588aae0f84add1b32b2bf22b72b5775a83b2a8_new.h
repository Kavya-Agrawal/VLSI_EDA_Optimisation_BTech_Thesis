// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48535487;
  double density_weight = 0.36912793;
  double prefix_weight = 0.36651701;
  double neighborhood_weight = 0.17416865;
  double late_weight = 0.03168924;
  double critical_weight = 0.35123319;
  unsigned budget = 36;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
