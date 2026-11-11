// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44847479;
  double density_weight = 0.57619909;
  double prefix_weight = 0.13751974;
  double neighborhood_weight = 0.09086219;
  double late_weight = 0.07461971;
  double critical_weight = 0.14379181;
  unsigned budget = 23;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
