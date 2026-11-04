// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22498684;
  double density_weight = 0.49552139;
  double prefix_weight = 0.06871482;
  double neighborhood_weight = 0.26601043;
  double late_weight = 0.08451551;
  double critical_weight = 0.23012546;
  unsigned budget = 7;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
