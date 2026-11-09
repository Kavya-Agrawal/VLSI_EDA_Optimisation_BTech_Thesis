// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24309099;
  double density_weight = 0.19844912;
  double prefix_weight = 0.15110715;
  double neighborhood_weight = 0.15394564;
  double late_weight = 0.00417907;
  double critical_weight = 0.40798221;
  unsigned budget = 39;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
