// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22690156;
  double density_weight = 0.14093131;
  double prefix_weight = 0.49348383;
  double neighborhood_weight = 0.29823918;
  double late_weight = 0.07808685;
  double critical_weight = 0.01060989;
  unsigned budget = 21;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
