// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24845448;
  double density_weight = 0.30502169;
  double prefix_weight = 0.39565358;
  double neighborhood_weight = 0.04263239;
  double late_weight = 0.12937427;
  double critical_weight = 0.32770250;
  unsigned budget = 13;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
