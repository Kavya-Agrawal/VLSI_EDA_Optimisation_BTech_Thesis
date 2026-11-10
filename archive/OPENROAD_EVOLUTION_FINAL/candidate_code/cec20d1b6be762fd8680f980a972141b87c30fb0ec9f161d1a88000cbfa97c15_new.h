// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62575149;
  double density_weight = 0.44559883;
  double prefix_weight = 0.46369768;
  double neighborhood_weight = 0.17725588;
  double late_weight = 0.15788241;
  double critical_weight = 0.35620794;
  unsigned budget = 6;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
