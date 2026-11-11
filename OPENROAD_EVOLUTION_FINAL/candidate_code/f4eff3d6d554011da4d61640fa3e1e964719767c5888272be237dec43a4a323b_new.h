// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87520367;
  double density_weight = 0.04339194;
  double prefix_weight = 0.28091447;
  double neighborhood_weight = 0.25852161;
  double late_weight = 0.22674021;
  double critical_weight = 0.14901706;
  unsigned budget = 5;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
