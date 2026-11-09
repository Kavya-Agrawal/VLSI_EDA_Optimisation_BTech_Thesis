// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88915047;
  double density_weight = 0.33770708;
  double prefix_weight = 0.04129064;
  double neighborhood_weight = 0.38269413;
  double late_weight = 0.16482859;
  double critical_weight = 0.49205373;
  unsigned budget = 13;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
