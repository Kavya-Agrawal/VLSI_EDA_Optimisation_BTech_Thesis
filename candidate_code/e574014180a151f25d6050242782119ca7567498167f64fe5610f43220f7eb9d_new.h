// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31443879;
  double density_weight = 0.48183465;
  double prefix_weight = 0.00350795;
  double neighborhood_weight = 0.39717333;
  double late_weight = 0.28438330;
  double critical_weight = 0.00767367;
  unsigned budget = 21;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
