// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26487177;
  double density_weight = 0.53808029;
  double prefix_weight = 0.10013304;
  double neighborhood_weight = 0.18471008;
  double late_weight = 0.15298495;
  double critical_weight = 0.10489273;
  unsigned budget = 8;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
