// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22549298;
  double density_weight = 0.17154485;
  double prefix_weight = 0.24472388;
  double neighborhood_weight = 0.05077117;
  double late_weight = 0.19971195;
  double critical_weight = 0.18023841;
  unsigned budget = 38;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
