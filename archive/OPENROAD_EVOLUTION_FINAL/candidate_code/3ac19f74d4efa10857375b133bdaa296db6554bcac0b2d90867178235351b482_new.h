// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80562491;
  double density_weight = 0.05006873;
  double prefix_weight = 0.43033535;
  double neighborhood_weight = 0.02160032;
  double late_weight = 0.18584952;
  double critical_weight = 0.34617783;
  unsigned budget = 40;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
