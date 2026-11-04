// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51817998;
  double density_weight = 0.55829620;
  double prefix_weight = 0.37112309;
  double neighborhood_weight = 0.22313573;
  double late_weight = 0.27961636;
  double critical_weight = 0.47353291;
  unsigned budget = 34;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
