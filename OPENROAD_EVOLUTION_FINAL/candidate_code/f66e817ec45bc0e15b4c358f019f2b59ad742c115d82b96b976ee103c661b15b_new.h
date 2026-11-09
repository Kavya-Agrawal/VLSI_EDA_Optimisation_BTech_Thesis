// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46879352;
  double density_weight = 0.06243876;
  double prefix_weight = 0.21830076;
  double neighborhood_weight = 0.21024818;
  double late_weight = 0.08492879;
  double critical_weight = 0.22953603;
  unsigned budget = 27;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
