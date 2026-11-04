// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17962539;
  double density_weight = 0.00392047;
  double prefix_weight = 0.45284849;
  double neighborhood_weight = 0.06972326;
  double late_weight = 0.25551293;
  double critical_weight = 0.46490151;
  unsigned budget = 40;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
