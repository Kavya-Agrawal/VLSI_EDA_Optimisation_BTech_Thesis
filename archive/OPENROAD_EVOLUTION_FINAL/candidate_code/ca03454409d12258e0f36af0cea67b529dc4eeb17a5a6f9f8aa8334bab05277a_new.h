// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80944233;
  double density_weight = 0.47426678;
  double prefix_weight = 0.18032302;
  double neighborhood_weight = 0.34721641;
  double late_weight = 0.02765137;
  double critical_weight = 0.48291765;
  unsigned budget = 39;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
