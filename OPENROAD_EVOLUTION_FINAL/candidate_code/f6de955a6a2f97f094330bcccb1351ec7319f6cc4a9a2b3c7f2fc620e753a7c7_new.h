// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87773350;
  double density_weight = 0.01358008;
  double prefix_weight = 0.06079759;
  double neighborhood_weight = 0.35102957;
  double late_weight = 0.00506693;
  double critical_weight = 0.23616446;
  unsigned budget = 26;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
