// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79830565;
  double density_weight = 0.40682665;
  double prefix_weight = 0.21673767;
  double neighborhood_weight = 0.14983887;
  double late_weight = 0.16187907;
  double critical_weight = 0.13079288;
  unsigned budget = 36;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
