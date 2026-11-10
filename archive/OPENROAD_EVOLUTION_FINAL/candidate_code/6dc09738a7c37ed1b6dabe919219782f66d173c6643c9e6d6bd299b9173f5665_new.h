// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82145279;
  double density_weight = 0.33197247;
  double prefix_weight = 0.00575811;
  double neighborhood_weight = 0.08962130;
  double late_weight = 0.03998414;
  double critical_weight = 0.45452056;
  unsigned budget = 13;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
