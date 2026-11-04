// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45954490;
  double density_weight = 0.52932678;
  double prefix_weight = 0.49998055;
  double neighborhood_weight = 0.19802189;
  double late_weight = 0.23479312;
  double critical_weight = 0.10174927;
  unsigned budget = 11;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
