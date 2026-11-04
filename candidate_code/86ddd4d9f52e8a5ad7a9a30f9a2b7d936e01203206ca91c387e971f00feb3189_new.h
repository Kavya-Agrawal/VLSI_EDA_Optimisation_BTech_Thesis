// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44198602;
  double density_weight = 0.08245739;
  double prefix_weight = 0.13098519;
  double neighborhood_weight = 0.09512453;
  double late_weight = 0.07912052;
  double critical_weight = 0.32312080;
  unsigned budget = 31;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
