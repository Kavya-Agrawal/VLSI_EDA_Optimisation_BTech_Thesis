// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12971244;
  double density_weight = 0.14908506;
  double prefix_weight = 0.40227434;
  double neighborhood_weight = 0.17065824;
  double late_weight = 0.07257433;
  double critical_weight = 0.43978372;
  unsigned budget = 31;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
