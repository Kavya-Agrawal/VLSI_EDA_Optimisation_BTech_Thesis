// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59936163;
  double density_weight = 0.33256323;
  double prefix_weight = 0.34960616;
  double neighborhood_weight = 0.04615016;
  double late_weight = 0.18230037;
  double critical_weight = 0.41794006;
  unsigned budget = 27;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
