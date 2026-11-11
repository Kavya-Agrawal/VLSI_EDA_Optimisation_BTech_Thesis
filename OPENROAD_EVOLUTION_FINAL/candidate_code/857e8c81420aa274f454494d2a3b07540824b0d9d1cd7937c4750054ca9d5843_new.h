// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70329000;
  double density_weight = 0.24496084;
  double prefix_weight = 0.33520815;
  double neighborhood_weight = 0.10096811;
  double late_weight = 0.09392328;
  double critical_weight = 0.47849804;
  unsigned budget = 33;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
