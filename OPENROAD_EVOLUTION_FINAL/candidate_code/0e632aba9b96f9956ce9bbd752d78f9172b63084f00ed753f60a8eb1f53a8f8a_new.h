// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39085265;
  double density_weight = 0.29194969;
  double prefix_weight = 0.35261273;
  double neighborhood_weight = 0.19027077;
  double late_weight = 0.00012858;
  double critical_weight = 0.02403527;
  unsigned budget = 6;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
