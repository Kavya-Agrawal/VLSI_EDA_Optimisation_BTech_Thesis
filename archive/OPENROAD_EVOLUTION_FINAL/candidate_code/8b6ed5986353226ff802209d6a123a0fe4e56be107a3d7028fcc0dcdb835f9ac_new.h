// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32186749;
  double density_weight = 0.33068429;
  double prefix_weight = 0.10795242;
  double neighborhood_weight = 0.19332613;
  double late_weight = 0.25979322;
  double critical_weight = 0.36067993;
  unsigned budget = 21;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
