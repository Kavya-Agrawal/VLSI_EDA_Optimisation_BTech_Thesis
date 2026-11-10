// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12977472;
  double density_weight = 0.33979927;
  double prefix_weight = 0.25334209;
  double neighborhood_weight = 0.20639893;
  double late_weight = 0.20670940;
  double critical_weight = 0.15806455;
  unsigned budget = 20;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
