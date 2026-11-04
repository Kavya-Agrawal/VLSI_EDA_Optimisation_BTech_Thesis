// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26886667;
  double density_weight = 0.15565096;
  double prefix_weight = 0.14162661;
  double neighborhood_weight = 0.03964147;
  double late_weight = 0.27186338;
  double critical_weight = 0.33436412;
  unsigned budget = 33;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
