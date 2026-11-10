// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41155633;
  double density_weight = 0.37888330;
  double prefix_weight = 0.00001521;
  double neighborhood_weight = 0.28380522;
  double late_weight = 0.29357164;
  double critical_weight = 0.06080122;
  unsigned budget = 26;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
