// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79931830;
  double density_weight = 0.57345767;
  double prefix_weight = 0.30893053;
  double neighborhood_weight = 0.32175959;
  double late_weight = 0.20554012;
  double critical_weight = 0.47742693;
  unsigned budget = 33;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
