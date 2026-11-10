// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02283140;
  double density_weight = 0.28873114;
  double prefix_weight = 0.08128762;
  double neighborhood_weight = 0.30854562;
  double late_weight = 0.01874957;
  double critical_weight = 0.20087408;
  unsigned budget = 40;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
