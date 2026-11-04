// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74803573;
  double density_weight = 0.47070135;
  double prefix_weight = 0.45528948;
  double neighborhood_weight = 0.28903048;
  double late_weight = 0.14284924;
  double critical_weight = 0.01194593;
  unsigned budget = 28;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
