// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04646902;
  double density_weight = 0.15661949;
  double prefix_weight = 0.23080483;
  double neighborhood_weight = 0.08146792;
  double late_weight = 0.08626778;
  double critical_weight = 0.24341859;
  unsigned budget = 19;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
