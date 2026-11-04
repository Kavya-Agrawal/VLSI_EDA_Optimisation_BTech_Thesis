// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75067486;
  double density_weight = 0.05554535;
  double prefix_weight = 0.30374905;
  double neighborhood_weight = 0.03529949;
  double late_weight = 0.26601937;
  double critical_weight = 0.29270888;
  unsigned budget = 26;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
