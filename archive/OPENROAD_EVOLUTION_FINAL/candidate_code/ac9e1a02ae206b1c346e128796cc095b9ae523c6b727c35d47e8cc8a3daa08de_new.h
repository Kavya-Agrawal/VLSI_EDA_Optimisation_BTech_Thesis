// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06093543;
  double density_weight = 0.24126379;
  double prefix_weight = 0.33812125;
  double neighborhood_weight = 0.13913990;
  double late_weight = 0.28313117;
  double critical_weight = 0.21977174;
  unsigned budget = 29;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
