// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67411221;
  double density_weight = 0.02448619;
  double prefix_weight = 0.14218062;
  double neighborhood_weight = 0.18732544;
  double late_weight = 0.08308374;
  double critical_weight = 0.26473658;
  unsigned budget = 13;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
