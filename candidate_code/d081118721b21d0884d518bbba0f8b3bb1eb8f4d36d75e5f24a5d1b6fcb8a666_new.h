// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43325628;
  double density_weight = 0.35060046;
  double prefix_weight = 0.00826248;
  double neighborhood_weight = 0.17016642;
  double late_weight = 0.16108050;
  double critical_weight = 0.42396031;
  unsigned budget = 14;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
