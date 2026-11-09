// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07132674;
  double density_weight = 0.17615396;
  double prefix_weight = 0.10985407;
  double neighborhood_weight = 0.37658733;
  double late_weight = 0.11654598;
  double critical_weight = 0.19506016;
  unsigned budget = 29;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
