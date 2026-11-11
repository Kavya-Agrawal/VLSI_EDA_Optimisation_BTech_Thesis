// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11731548;
  double density_weight = 0.35675269;
  double prefix_weight = 0.49300462;
  double neighborhood_weight = 0.22455927;
  double late_weight = 0.27060896;
  double critical_weight = 0.07755436;
  unsigned budget = 34;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
