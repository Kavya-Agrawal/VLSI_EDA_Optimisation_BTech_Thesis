// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36565309;
  double density_weight = 0.50706213;
  double prefix_weight = 0.05137844;
  double neighborhood_weight = 0.00624020;
  double late_weight = 0.17996107;
  double critical_weight = 0.39538588;
  unsigned budget = 31;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
