// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55432569;
  double density_weight = 0.46195951;
  double prefix_weight = 0.27598204;
  double neighborhood_weight = 0.30934281;
  double late_weight = 0.23743226;
  double critical_weight = 0.41493402;
  unsigned budget = 19;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
