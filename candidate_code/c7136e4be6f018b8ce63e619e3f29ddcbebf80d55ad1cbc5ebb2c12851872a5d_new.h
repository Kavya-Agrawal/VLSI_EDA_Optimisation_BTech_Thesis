// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39017973;
  double density_weight = 0.28147713;
  double prefix_weight = 0.28720291;
  double neighborhood_weight = 0.06434939;
  double late_weight = 0.18161054;
  double critical_weight = 0.43179449;
  unsigned budget = 6;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
