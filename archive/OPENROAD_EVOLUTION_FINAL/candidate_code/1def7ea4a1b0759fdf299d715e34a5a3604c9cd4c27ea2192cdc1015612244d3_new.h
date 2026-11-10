// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48185578;
  double density_weight = 0.46568112;
  double prefix_weight = 0.07966838;
  double neighborhood_weight = 0.09873560;
  double late_weight = 0.08971559;
  double critical_weight = 0.48944011;
  unsigned budget = 20;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
