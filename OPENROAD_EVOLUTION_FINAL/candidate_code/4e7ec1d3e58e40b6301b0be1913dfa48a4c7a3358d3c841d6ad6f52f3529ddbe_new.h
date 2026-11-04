// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82627429;
  double density_weight = 0.20245387;
  double prefix_weight = 0.32868616;
  double neighborhood_weight = 0.12130321;
  double late_weight = 0.24733925;
  double critical_weight = 0.46429479;
  unsigned budget = 24;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
