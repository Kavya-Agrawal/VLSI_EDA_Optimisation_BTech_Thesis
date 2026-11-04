// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90752481;
  double density_weight = 0.11532560;
  double prefix_weight = 0.32534733;
  double neighborhood_weight = 0.16818323;
  double late_weight = 0.23514450;
  double critical_weight = 0.23077924;
  unsigned budget = 10;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
