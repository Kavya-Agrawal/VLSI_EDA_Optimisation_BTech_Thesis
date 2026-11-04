// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90358537;
  double density_weight = 0.59373312;
  double prefix_weight = 0.48988780;
  double neighborhood_weight = 0.28956826;
  double late_weight = 0.24505767;
  double critical_weight = 0.28978735;
  unsigned budget = 34;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
