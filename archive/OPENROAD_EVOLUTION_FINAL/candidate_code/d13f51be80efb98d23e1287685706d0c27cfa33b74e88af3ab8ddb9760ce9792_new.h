// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22767532;
  double density_weight = 0.52871633;
  double prefix_weight = 0.45777149;
  double neighborhood_weight = 0.32741068;
  double late_weight = 0.10370609;
  double critical_weight = 0.49459345;
  unsigned budget = 40;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
