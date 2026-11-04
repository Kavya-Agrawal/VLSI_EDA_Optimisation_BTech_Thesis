// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39485159;
  double density_weight = 0.48162787;
  double prefix_weight = 0.27663024;
  double neighborhood_weight = 0.34130367;
  double late_weight = 0.09413735;
  double critical_weight = 0.23231764;
  unsigned budget = 17;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
