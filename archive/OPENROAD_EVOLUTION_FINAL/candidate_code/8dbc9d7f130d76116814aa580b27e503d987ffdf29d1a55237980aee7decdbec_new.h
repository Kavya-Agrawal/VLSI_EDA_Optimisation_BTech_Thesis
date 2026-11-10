// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94673608;
  double density_weight = 0.16592914;
  double prefix_weight = 0.35491007;
  double neighborhood_weight = 0.13417536;
  double late_weight = 0.08337168;
  double critical_weight = 0.27457198;
  unsigned budget = 30;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
