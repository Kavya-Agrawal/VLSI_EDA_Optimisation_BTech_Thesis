// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63229745;
  double density_weight = 0.12011103;
  double prefix_weight = 0.09568065;
  double neighborhood_weight = 0.20335191;
  double late_weight = 0.04553077;
  double critical_weight = 0.12492860;
  unsigned budget = 34;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
