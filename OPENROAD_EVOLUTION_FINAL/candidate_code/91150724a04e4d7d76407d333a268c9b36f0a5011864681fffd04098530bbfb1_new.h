// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47202615;
  double density_weight = 0.20886349;
  double prefix_weight = 0.00302317;
  double neighborhood_weight = 0.18085778;
  double late_weight = 0.21406401;
  double critical_weight = 0.12827569;
  unsigned budget = 29;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
