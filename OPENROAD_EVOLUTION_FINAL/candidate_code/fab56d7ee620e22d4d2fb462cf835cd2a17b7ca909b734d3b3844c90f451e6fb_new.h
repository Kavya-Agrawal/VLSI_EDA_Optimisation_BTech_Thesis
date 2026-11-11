// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62885190;
  double density_weight = 0.29605549;
  double prefix_weight = 0.47137014;
  double neighborhood_weight = 0.14697865;
  double late_weight = 0.07237775;
  double critical_weight = 0.38905713;
  unsigned budget = 40;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
