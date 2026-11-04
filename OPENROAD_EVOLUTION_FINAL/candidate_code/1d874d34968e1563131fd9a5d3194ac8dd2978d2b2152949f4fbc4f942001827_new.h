// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19371646;
  double density_weight = 0.34174211;
  double prefix_weight = 0.48774826;
  double neighborhood_weight = 0.32180675;
  double late_weight = 0.04611987;
  double critical_weight = 0.21526515;
  unsigned budget = 20;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
