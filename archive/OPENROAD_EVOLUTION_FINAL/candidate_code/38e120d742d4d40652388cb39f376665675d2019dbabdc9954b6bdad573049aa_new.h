// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46009827;
  double density_weight = 0.24386845;
  double prefix_weight = 0.42614361;
  double neighborhood_weight = 0.34628708;
  double late_weight = 0.17953051;
  double critical_weight = 0.14898943;
  unsigned budget = 12;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
