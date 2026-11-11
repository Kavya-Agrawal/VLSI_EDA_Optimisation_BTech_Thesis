// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90174399;
  double density_weight = 0.29051336;
  double prefix_weight = 0.06655864;
  double neighborhood_weight = 0.10181282;
  double late_weight = 0.18476739;
  double critical_weight = 0.13262937;
  unsigned budget = 7;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
