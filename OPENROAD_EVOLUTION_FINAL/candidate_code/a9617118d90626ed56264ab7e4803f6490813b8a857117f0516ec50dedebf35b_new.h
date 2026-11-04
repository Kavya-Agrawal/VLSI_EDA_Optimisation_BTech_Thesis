// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45509062;
  double density_weight = 0.41937994;
  double prefix_weight = 0.27616579;
  double neighborhood_weight = 0.22988950;
  double late_weight = 0.26921798;
  double critical_weight = 0.47078203;
  unsigned budget = 20;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
