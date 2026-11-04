// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51488059;
  double density_weight = 0.06433135;
  double prefix_weight = 0.33167318;
  double neighborhood_weight = 0.13690183;
  double late_weight = 0.11935197;
  double critical_weight = 0.28593671;
  unsigned budget = 32;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
