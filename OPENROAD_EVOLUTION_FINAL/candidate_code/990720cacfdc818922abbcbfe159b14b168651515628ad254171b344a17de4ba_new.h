// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86543852;
  double density_weight = 0.35236955;
  double prefix_weight = 0.36487764;
  double neighborhood_weight = 0.13183746;
  double late_weight = 0.09470539;
  double critical_weight = 0.49080467;
  unsigned budget = 28;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
