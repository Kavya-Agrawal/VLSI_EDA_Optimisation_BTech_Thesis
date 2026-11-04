// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71383072;
  double density_weight = 0.37628533;
  double prefix_weight = 0.39824384;
  double neighborhood_weight = 0.28893709;
  double late_weight = 0.22113368;
  double critical_weight = 0.05846526;
  unsigned budget = 8;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
