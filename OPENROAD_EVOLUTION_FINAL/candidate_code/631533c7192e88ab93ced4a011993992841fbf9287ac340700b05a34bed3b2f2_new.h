// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80995504;
  double density_weight = 0.53114894;
  double prefix_weight = 0.03399718;
  double neighborhood_weight = 0.24349957;
  double late_weight = 0.07754663;
  double critical_weight = 0.32453100;
  unsigned budget = 8;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
