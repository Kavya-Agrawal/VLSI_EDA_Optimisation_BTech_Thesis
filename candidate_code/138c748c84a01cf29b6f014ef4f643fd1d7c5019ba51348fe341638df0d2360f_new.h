// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94888897;
  double density_weight = 0.10616415;
  double prefix_weight = 0.33238968;
  double neighborhood_weight = 0.16222584;
  double late_weight = 0.09015937;
  double critical_weight = 0.40547070;
  unsigned budget = 32;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
