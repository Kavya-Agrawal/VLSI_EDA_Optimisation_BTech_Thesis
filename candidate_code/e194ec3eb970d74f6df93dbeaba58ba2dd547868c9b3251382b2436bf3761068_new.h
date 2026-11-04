// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42129551;
  double density_weight = 0.12024617;
  double prefix_weight = 0.02603681;
  double neighborhood_weight = 0.04575116;
  double late_weight = 0.18077213;
  double critical_weight = 0.05281353;
  unsigned budget = 39;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
