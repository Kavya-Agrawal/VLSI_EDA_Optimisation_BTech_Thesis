// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10147900;
  double density_weight = 0.41125918;
  double prefix_weight = 0.24071254;
  double neighborhood_weight = 0.15847023;
  double late_weight = 0.11568567;
  double critical_weight = 0.20819342;
  unsigned budget = 25;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
