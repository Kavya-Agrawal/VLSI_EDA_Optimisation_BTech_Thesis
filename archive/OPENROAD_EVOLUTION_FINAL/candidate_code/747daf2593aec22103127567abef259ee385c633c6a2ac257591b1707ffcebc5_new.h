// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45654320;
  double density_weight = 0.26513514;
  double prefix_weight = 0.01774503;
  double neighborhood_weight = 0.03822195;
  double late_weight = 0.15340897;
  double critical_weight = 0.19540265;
  unsigned budget = 28;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
