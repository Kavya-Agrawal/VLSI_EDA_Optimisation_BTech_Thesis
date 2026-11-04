// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13291701;
  double density_weight = 0.28427710;
  double prefix_weight = 0.15279008;
  double neighborhood_weight = 0.24881935;
  double late_weight = 0.19918872;
  double critical_weight = 0.33846872;
  unsigned budget = 15;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
