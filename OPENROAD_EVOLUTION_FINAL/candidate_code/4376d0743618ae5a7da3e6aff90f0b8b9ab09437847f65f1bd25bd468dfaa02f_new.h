// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49936684;
  double density_weight = 0.01383434;
  double prefix_weight = 0.06173700;
  double neighborhood_weight = 0.11358073;
  double late_weight = 0.21988298;
  double critical_weight = 0.01741348;
  unsigned budget = 36;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
