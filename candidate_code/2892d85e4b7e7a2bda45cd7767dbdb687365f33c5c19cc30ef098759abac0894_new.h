// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72927725;
  double density_weight = 0.41372184;
  double prefix_weight = 0.14550954;
  double neighborhood_weight = 0.19318753;
  double late_weight = 0.07720660;
  double critical_weight = 0.38967380;
  unsigned budget = 24;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
