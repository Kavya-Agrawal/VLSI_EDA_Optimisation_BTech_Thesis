// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91504930;
  double density_weight = 0.33370501;
  double prefix_weight = 0.31055038;
  double neighborhood_weight = 0.33161396;
  double late_weight = 0.17832260;
  double critical_weight = 0.17231982;
  unsigned budget = 22;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
