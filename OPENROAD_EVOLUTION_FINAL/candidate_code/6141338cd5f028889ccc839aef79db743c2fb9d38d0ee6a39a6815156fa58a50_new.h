// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21292787;
  double density_weight = 0.29658286;
  double prefix_weight = 0.27454492;
  double neighborhood_weight = 0.27444228;
  double late_weight = 0.01432316;
  double critical_weight = 0.02363053;
  unsigned budget = 27;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
