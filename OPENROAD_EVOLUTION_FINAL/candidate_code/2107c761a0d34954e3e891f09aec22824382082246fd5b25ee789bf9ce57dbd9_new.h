// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33344594;
  double density_weight = 0.16378294;
  double prefix_weight = 0.40102504;
  double neighborhood_weight = 0.02482053;
  double late_weight = 0.10444790;
  double critical_weight = 0.16263608;
  unsigned budget = 22;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
