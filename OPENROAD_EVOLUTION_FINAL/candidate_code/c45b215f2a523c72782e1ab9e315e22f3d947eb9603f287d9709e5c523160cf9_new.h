// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70512153;
  double density_weight = 0.59544338;
  double prefix_weight = 0.21989344;
  double neighborhood_weight = 0.28712127;
  double late_weight = 0.12851329;
  double critical_weight = 0.02044839;
  unsigned budget = 12;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
