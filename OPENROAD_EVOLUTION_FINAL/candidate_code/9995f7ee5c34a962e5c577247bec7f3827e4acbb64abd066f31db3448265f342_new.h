// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21923264;
  double density_weight = 0.49162018;
  double prefix_weight = 0.06541349;
  double neighborhood_weight = 0.15675802;
  double late_weight = 0.06881850;
  double critical_weight = 0.33745342;
  unsigned budget = 36;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
